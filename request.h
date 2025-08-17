#ifdef REQUEST_SERVER

__attribute__((warning(("fungsi ini belum sempurna jadi masih ada kemungkinan bug"))))
extern void *get_page(const char *getreq);
extern void *get_login_page(const char *username,const char *password);

#endif

