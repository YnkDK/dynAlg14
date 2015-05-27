/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** performance.h
** Implementation of the performance tests. 
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/
#include "performance.h"

#include <iostream>

const std::string outputDir("output/");
const std::string insSuffix("-ins.stat");
const std::string delSuffix("-del.stat");
const std::string querySuffix("-query.stat");
const std::string queryOutSuffix(".out");

void Performance::run(
        std::vector<TC *> algs,        //< Algorithms to be executed
        std::vector<Input> changes, //< Changes as defined in project description
        std::string output_prefix)    //< e.g. output/changefile3-ins.stat
{

    // Open output streams
    std::ofstream insFile(outputDir + output_prefix + insSuffix);
    std::ofstream delFile(outputDir + output_prefix + delSuffix);
    std::ofstream queryFile(outputDir + output_prefix + querySuffix);

    //
    unsigned int querySize;
    long long cpuClock;
    for (auto &alg : algs) {
        const char *name = alg->get_name();
        std::string strName(name, strlen(name));
        std::ofstream queryOutFile(outputDir + output_prefix + strName + queryOutSuffix);
        for (auto &change : changes) {
            switch (change.type) {
                case 4:
                    alg->jump(change.state);
                    break;
                case 3:
                    alg->init(change.i);
                    break;
                case 2:
                    // Reset counters
                    ioctl(this->fd, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                    // Start counting
                    ioctl(this->fd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
                    // Run query
                    querySize = alg->query();
                    // Stop counting
                    ioctl(this->fd, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                    // Get CPU clock count
                    cpuClock = _get(PERF_TYPE_SOFTWARE, PERF_COUNT_SW_CPU_CLOCK);
                    // Write cpu time
                    queryFile << name << "," << cpuClock << "\n";
                    // Write output (for correctness)
                    queryOutFile << querySize << "\n";
                    break;
                case 1:
                    // Reset counters
                    ioctl(this->fd, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                    // Start counting
                    ioctl(this->fd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
                    // Run query
                    alg->del(change.i, change.j);
                    // Stop counting
                    ioctl(this->fd, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                    // Get CPU clock count
                    cpuClock = _get(PERF_TYPE_SOFTWARE, PERF_COUNT_SW_CPU_CLOCK);
                    // Write cpu time
                    delFile << name << "," << cpuClock << "\n";
                    break;
                case 0:
                    // Reset counters
                    ioctl(this->fd, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
                    // Start counting
                    ioctl(this->fd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
                    // Run query
                    alg->ins(change.i, change.j);
                    // Stop counting
                    ioctl(this->fd, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
                    // Get CPU clock count
                    cpuClock = _get(PERF_TYPE_SOFTWARE, PERF_COUNT_SW_CPU_CLOCK);
                    // Write cpu time
                    insFile << name << "," << cpuClock << "\n";
                    break;
                default:
                    std::cout << "ERROR!!" << std::endl;
                    // Close all files
                    queryOutFile.close();
                    insFile.close();
                    delFile.close();
                    queryFile.close();
                    return;
            }
        }
        queryOutFile.close();
    }
    insFile.close();
    delFile.close();
    queryFile.close();
}


static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags) {
    int ret;

    ret = syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);

    return ret;
}

void Performance::_add(perf_type_id type, long long config) {
    struct perf_event_attr pe;
    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.size = sizeof(struct perf_event_attr);
    pe.exclude_kernel = 1;
    pe.exclude_hv = 1;

    pe.type = type;
    pe.config = config;


    order[events].type = type;
    order[events].config = config;
    events++;

    if (fd == -1) {
        /* if changed: change calculations in get */
        pe.read_format = PERF_FORMAT_GROUP;
        pe.disabled = 1;

        fd = perf_event_open(&pe, 0, -1, -1, 0);
        if (fd < 0) {
            fprintf(stderr, "Error opening leader for %llx / %llx\n", (long long) type, config);
            exit(EXIT_FAILURE);
        }
    } else {
        int ret = perf_event_open(&pe, 0, -1, fd, 0);
        if (ret < 0) {
            fprintf(stderr, "Error connecting to leader for %llx / %llx\n", (long long) type, config);
            exit(EXIT_FAILURE);
        }
    }
}

long long Performance::_get(perf_type_id type, long long config) {
    long long buffer[1 /* <nr> */ + (1 /* <value> */ * perf_size /* [nr] */)];
    int readSize = (1 + (1 * perf_size)) * sizeof(long long);
    int r = read(fd, &buffer, readSize);
    if (r == -1) {
        fprintf(stderr, "Error reading from fd\n");
        exit(EXIT_FAILURE);
    }
    for (int index = 0; index < events; index++) {
        if (order[index].config == config && order[index].type == type) {
            return buffer[1 + index];
        }
    }
    fprintf(stderr, "Could not find sw config: %llx\n", (long long) config);
    exit(EXIT_FAILURE);
}
