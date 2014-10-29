#ifndef _USER_H
#define _USER_H

namespace cobaya {

int logout_client(const char *user);
int logon_client(const char *user, const char *passwd, const char *host);
int update_user(const char *user, const char *passwd, const char *host);

} // namespace cobaya

#endif /* _USER_H */
