/* Taken from  https://gitlab.kitware.com/cmake/community/-/wikis/contrib/macros/TestInline
 * for using "inline" with cmake build. */
/* Test source lifted from /usr/share/autoconf/autoconf/c.m4 */
typedef int foo_t;
static inline foo_t static_foo(){return 0;}
foo_t foo(){return 0;}
int main(int argc, char *argv[]){return 0;}
