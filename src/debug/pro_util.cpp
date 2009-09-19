#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define USE_DANGEROUS_FUNCTIONS
#include "pro.h"

idaman void *ida_export qalloc( size_t size )
{
  return malloc(size);
}

idaman void *ida_export qalloc_or_throw(size_t size)
{
 return qalloc(size);
}

idaman void *ida_export qrealloc_or_throw(void *ptr, size_t size)
{
  return realloc(ptr, size);
}

idaman void  ida_export qfree( void *alloc )
{
  free(alloc);
}

idaman NORETURN void ida_export qexit(int code)
{
 exit(code);
}

idaman int ida_export qerrcode(int new_code=-1)
{
 return errno;
}

idaman const char *ida_export qerrstr(int code=-1)
{
  if(code == -1)
    code = qerrcode();

  return strerror(code);
}

idaman char *ida_export winerr(int code)
{
  return ""; //FIXME
}

idaman int ida_export qvprintf(const char *fmt, va_list va)
{
 return vprintf(fmt, va);
}

idaman NORETURN void ida_export verror(const char *message, va_list va)
{
  printf("verror: ");
  qvprintf(message, va);

  qexit(1);
}

idaman int ida_export qsnprintf(char *buffer, size_t n, const char *format, ...) 
{
  int ret;
  va_list va;

  va_start(va, format);
  ret = vsnprintf(buffer, n, format, va);
  va_end(va);

  if(ret > 0) //IDA returns the amount written excluding the terminating '\0'
   ret--;

  return ret;
}

idaman char *ida_export qstrncpy(char *dst, const char *src, size_t dstsize)
{
  return strncpy(dst, src, dstsize);
}

inline uchar *put_dw(uchar *ptr, uchar *end, ushort x)
{
  //QBUFCHECK(ptr, end-ptr, NULL);
  if ( ptr < end )
    *ptr++ = (uchar)(x>>8);
  if ( ptr < end )
    *ptr++ = (uchar)(x);
  return ptr;
}

inline ushort get_dw(const uchar **pptr, const uchar *end)
{
  ushort x = 0;
  const uchar *ptr = *pptr;
  if ( ptr < end )
    x = (*ptr++) << 8;
  if ( ptr < end )
    x |= *ptr++;
  *pptr = ptr;
  return x;
}

inline uchar *pack_db(uchar *ptr, uchar *end, uchar x)
{
  if ( ptr < end )
    *ptr++ = x;
  return ptr;
}

//-----------------------------------------------------------------------
idaman uchar    *ida_export pack_dd(uchar *ptr, uchar *end, uint32 x)
{
  QBUFCHECK(ptr, end-ptr, NULL);
  if ( x <= 0x7F )
    return pack_db(ptr, end, (uchar)(x));
  if ( x <= 0x3FFF )
    return put_dw(ptr, end, ushort(x|0x8000));
  if ( x <= 0x1FFFFFFFL )
  {
    ptr = put_dw(ptr, end, ushort((x>>16)|0xC000));
    return put_dw(ptr, end, ushort(x));
  }
  *ptr++ = 0xFF;
  ptr = put_dw(ptr, end, ushort((x>>16)));
  return put_dw(ptr, end, ushort(x));
}

//-----------------------------------------------------------------------
idaman uint32    ida_export unpack_dd(const uchar **pptr, const uchar *end)
{
  const uchar *ptr = *pptr;
  uint32 x = 0;
  if ( ptr < end )
    x = *ptr++;
  if ( (x & 0x80) == 0x80 )
  {
    if ( (x & 0xC0) == 0xC0 )
    {
      ushort low, high;
      if ( (x & 0xE0) == 0xE0 )
      {
        high = get_dw(&ptr, end);
        low  = get_dw(&ptr, end);
      }
      else
      {
        if ( ptr < end )
          high = ushort(((x & ~0xC0) << 8) + *ptr++);
        else
          high = 0;
        low = get_dw(&ptr, end);
      }
      x = (long(high)<<16) + low;
    }
    else
    {
      if ( ptr < end )
        x = ((x & ~0x80)<<8) + *ptr++;
    }
  }
  *pptr = ptr;
  return x;
}

idaman FILE *ida_export qfopen(const char *file, const char *mode)
{
  return fopen(file, mode);
}

idaman int ida_export qfread(FILE *fp, void *buf, size_t n)
{
  return fread(buf, 1, n, fp);
}

idaman int ida_export qfwrite(FILE *fp, const void *buf, size_t n)
{
  return fwrite(buf, 1, n, fp);
}

idaman int ida_export qfseek(FILE *fp, int32 offset, int whence)
{
  return fseek(fp, offset, whence);
}

idaman int ida_export qfclose(FILE *fp)
{
  return fclose(fp);
}


idaman int ida_export qveprintf(const char *fmt, va_list va)
{
  return qvprintf(fmt, va);
}

idaman int ida_export qvsnprintf(char *buffer, size_t n, const char *format, va_list va)
{
  return vsnprintf(buffer, n, format, va);
}

idaman char *ida_export qstrdup( const char *string )
{
 return strdup(string);
}

idaman void ida_export reg_hit_counter(hit_counter_t *hc, bool do_reg)
{
  return;
}

idaman hit_counter_t *ida_export create_hit_counter(const char *name)
{
  //I got "Undefined reference to 'vtable for ...'" messages when compiling using new and the hit_counter_t constructor
  //so I'm doing it the old fashioned way.
  struct hit_counter_t *hc = (struct hit_counter_t *)malloc(sizeof(struct hit_counter_t));
  hc->name = name;

  hc->total = 0;
  hc->misses = 0;
  hc->elapsed = 0;
  hc->stamp = 0;
 
  return hc;
}

idaman void ida_export hit_counter_timer(hit_counter_t *hc, bool enable)
{
  return;
}

idaman void *ida_export open_linput(const char *file, bool remote)
{
  return NULL;
}

class linput_t
{
};

idaman void ida_export close_linput(linput_t *li)
{
  return;
}

idaman uint32 ida_export calc_file_crc32(linput_t *fp)
{
  return 0;
}

idaman uint32 ida_export efilelength(FILE *fp)
{
 uint32 cur_pos = ftell(fp);
 uint32 len;

 fseek(fp, 0, SEEK_END);

 len = ftell(fp);

 fseek(fp, cur_pos, SEEK_SET);

 return len;  
}

idaman FILE *ida_export fopenWB(const char *file)
{
  return qfopen(file, "wb");
}

idaman FILE *ida_export fopenRB(const char *file)
{
  return qfopen(file, "rb");
}

//stubs for callui_t and ui_notification_t
union callui_t          // Return codes (size of this type should be 4 bytes at most)
{
 uint32 padding; 
};

enum ui_notification_t
{
 ui_temp = 1000
};

idaman callui_t ida_export_data /*idaapi*/ callui(ui_notification_t what, va_list va)
{
  callui_t i;
  i.padding = 1;
  return i;
}

idaman void ida_export vshow_hex(const void *dataptr,size_t len,const char *fmt, va_list va)
{
  return;
}

int idados_msg(const char *format, ...)
{
  int ret;
  va_list va;

  va_start(va, format);
  ret = qvprintf(format, va); 
  va_end(va);

  return ret;
}


