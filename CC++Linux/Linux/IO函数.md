```c++
int open(const char *pathname, int flags); 

int open(const char *pathname, int flags, mode_t mode);

int close(int fd);  


ssize_t read(int fd, void *buf, size_t count); 

ssize_t write(int fd, const void *buf, size_t count); 

off_t lseek(int fd, off_t offset, int whence); 

int stat(const char *pathname, struct stat *statbuf);  

int lstat(const char *pathname, struct stat *statbuf)



int access(const char *pathname, int mode); 

int chmod(const char *filename, int mode); 

int chown(const char *path, uid_t owner, gid_t group);

 int truncate(const char *path, off_t length);



int rename(const char *oldpath, const char *newpath); 

int chdir(const char *path); 

char *getcwd(char *buf, size_t size); 

int mkdir(const char *pathname, mode_t mode); 

int rmdir(const char *pathname);



DIR *opendir(const char *name); 

struct dirent *readdir(DIR *dirp); 

int closedir(DIR *dirp);

int dup(int oldfd);
int dup2(int oldfd, int newfd);
int dup3(int oldfd, int newfd, int flags);
```



