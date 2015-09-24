/* Z-machine specific definitions.
 * (C) 2001 David Given
 */

#ifndef Z_H
#define Z_H

void set_output_stream_buffer(int* buffer) = "\t@output_stream 3 r0;\n";
void reset_output_stream(void) = "\t@output_stream -3;\n";
void print_packed(int addr) = "\t@print_paddr r0;\n";
void printnum(int i) = "\t@print_num r0;\n";
void printchar(int i) = "\t@print_char r0;\n";
void set_window(int win) = "\t@set_window r0;\n";
void nl(void) = "\t@print_char 13;\n";
void quit(void) = "\t@quit;\n";
int random(int range) = "\t@random r0 -> r0;\n";

#endif

