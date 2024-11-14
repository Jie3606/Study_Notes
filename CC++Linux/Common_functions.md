# 获取时间

```c
struct timeval now = {0, 0};
gettimeofday(&now, nullptr);
time_t tSec = now.tv_sec;
struct tm *sysTime = localtime(&tSec);
struct tm t = *sysTime;

struct timeval
{
	long tv_sec;
	long tv_usec;
};
struct tm {
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
};
struct timespec {
  std::time_t tv_sec;
  long tv_nsec;
};
```

# 可变参

```c++
va_list vaList;
va_start(vaList, format);
int m = vsnprintf(buff_.BeginWrite(), buff_.WritableBytes(), format, vaList);
va_end(vaList);
```

