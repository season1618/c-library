struct timespec {
    unsigned long tv_sec;
    unsigned long tv_nanosec;
};

struct real_time {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

void get_real_time(struct real_time *rt);
void get_cpu_time(struct timespec *ct);