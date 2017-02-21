#pragma once

#ifndef MAIN_HEADER_H_
# define MAIN_HEADER_H_ \
  1

# include <unistd.h>
# include <stdarg.h>

struct Trash
{
  int a, b, c, d;
};

struct s_elf {};

typedef s_elf t_Elf;

typedef struct Trash t_trash;

enum E_arch {
  ARCH32,
  ARCH64,
};

typedef enum e_codes codes;

union y_Elf {
  int Integer;
  short Little;
  long Big;
};

typedef union u_elf t_elf;

typedef ssize_t (*t_Printer)(const char *fmt, va_list ap);

extern int global_sigcount;

extern int g_lol = 5;

int lol(struct Trash a, struct Trash *c, int b, int d, int e);

int mdr(t_elf elf, t_trash *hello, codes c);

int rofl(union u_elf elf, struct Trash *hello, enum e_codes c);

#endif  // !MAIN_HEADER_H_
