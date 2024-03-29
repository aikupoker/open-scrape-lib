#ifndef INC_LOOKUP3_H
#define INC_LOOKUP3_H

uint32_t hashword(
  const uint32_t *k,                   /* the key, an array of uint32_t values */
  size_t          length,               /* the length of the key, in uint32_ts */
  uint32_t        initval
);

#endif // INC_LOOKUP3_H