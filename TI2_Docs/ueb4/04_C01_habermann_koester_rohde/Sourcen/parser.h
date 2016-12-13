struct command {
  char **argv;
  int background;
};

#ifdef __cplusplus
extern "C"
{
#endif

struct command read_command_line();

#ifdef __cplusplus
}
#endif
