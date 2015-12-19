/*
 *  An 32-bit implementation of the XTEA algorithm
 *
 *  Copyright (C) 2006-2014, Brainspark B.V.
 *
 *  This file is part of PolarSSL (http://www.polarssl.org)
 *  Lead Maintainer: Paul Bakker <polarssl_maintainer at polarssl.org>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#define POLARSSL_XTEA_C

#if !defined(POLARSSL_CONFIG_FILE)
//#include "polarssl/config.h"
#else
#include POLARSSL_CONFIG_FILE
#endif

#if defined(POLARSSL_XTEA_C)

#include "xtea.h"

#if defined(POLARSSL_PLATFORM_C)
#include "polarssl/platform.h"
#else
#define polarssl_printf printf
#endif

#if !defined(POLARSSL_XTEA_ALT)

/* Implementation that should never be optimized out by the compiler */
static void polarssl_zeroize( void *v, size_t n ) {
    volatile unsigned char *p = v; while( n-- ) *p++ = 0;
}

/*
 * 32-bit integer manipulation macros (big endian)
 */
#ifndef GET_UINT32_BE
#define GET_UINT32_BE(n,b,i)                            \
{                                                       \
    (n) = ( (uint32_t) (b)[(i)    ] << 24 )             \
        | ( (uint32_t) (b)[(i) + 1] << 16 )             \
        | ( (uint32_t) (b)[(i) + 2] <<  8 )             \
        | ( (uint32_t) (b)[(i) + 3]       );            \
}
#endif

#ifndef PUT_UINT32_BE
#define PUT_UINT32_BE(n,b,i)                            \
{                                                       \
    (b)[(i)    ] = (unsigned char) ( (n) >> 24 );       \
    (b)[(i) + 1] = (unsigned char) ( (n) >> 16 );       \
    (b)[(i) + 2] = (unsigned char) ( (n) >>  8 );       \
    (b)[(i) + 3] = (unsigned char) ( (n)       );       \
}
#endif

// Almir: defined but not used
//static void xtea_init( xtea_context *ctx )
//{
//    memset( ctx, 0, sizeof( xtea_context ) );
//}

static void xtea_free( xtea_context *ctx )
{
    if( ctx == NULL )
        return;

    polarssl_zeroize( ctx, sizeof( xtea_context ) );
}

/*
 * XTEA key schedule
 */
static void xtea_setup( xtea_context *ctx, const unsigned char key[16] )
{
    int i;

    memset( ctx, 0, sizeof(xtea_context) );

    for( i = 0; i < 4; i++ )
    {
        GET_UINT32_BE( ctx->k[i], key, i << 2 );
    }
}

/*
 * XTEA encrypt function
 */
static int xtea_crypt_ecb( xtea_context *ctx, int mode,
                    const unsigned char input[8], unsigned char output[8])
{
    uint32_t *k, v0, v1, i;

    k = ctx->k;

    GET_UINT32_BE( v0, input, 0 );
    GET_UINT32_BE( v1, input, 4 );

    if( mode == XTEA_ENCRYPT )
    {
        uint32_t sum = 0, delta = 0x9E3779B9;

        for( i = 0; i < 32; i++ )
        {
            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
            sum += delta;
            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum>>11) & 3]);
        }
    }
    else /* XTEA_DECRYPT */
    {
        uint32_t delta = 0x9E3779B9, sum = delta * 32;

        for( i = 0; i < 32; i++ )
        {
            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum>>11) & 3]);
            sum -= delta;
            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
        }
    }

    PUT_UINT32_BE( v0, output, 0 );
    PUT_UINT32_BE( v1, output, 4 );

    return( 0 );
}

int xtea_crypt(uint8_t * input, uint8_t input_size, uint8_t * output, uint8_t output_size,
		uint8_t * key, uint8_t mode)
{
	if ((XTEA_ENCRYPT == mode && (output_size % 8 != 0 || input_size > output_size)) ||
		(XTEA_DECRYPT == mode && output_size < input_size))
	{
		return 0;
	}

	xtea_context ctx;
	xtea_setup(&ctx, key);

	uint8_t i;
	for (i = 0; i < input_size; i += 8)
	{
		uint8_t crypt[8] = { 0 };
		uint8_t crypt_len = input_size - i;
		if (crypt_len > 8)
		{
			crypt_len = 8;
		}

		memcpy(crypt, input + i, crypt_len);

		xtea_crypt_ecb(&ctx, mode, crypt, output + i);
	}

	xtea_free(&ctx);

	return 1;
}


//uint8_t xtea_crypted_size(uint8_t plain_text_size)
//{
//	uint8_t crypted_size = 0;
//	crypted_size = plain_text_size / 8;
//	crypted_size += plain_text_size % 8 != 0 ? 1 : 0;
//	crypted_size *= 8;
//
//	return crypted_size;
//}



unsigned char charset[]={"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789*-"};

unsigned char revchar(char ch)
{
   if (ch >= 'A' && ch <= 'Z')
      ch -= 'A';
   else if (ch >= 'a' && ch <='z')
      ch = ch - 'a' + 26;
   else if (ch >= '0' && ch <='9')
      ch = ch - '0' + 52;
   else if (ch == '*')
      ch = 62;
   else if (ch == '-')
      ch = 63;
   return(ch);
}

int base64_encode(unsigned char in[], unsigned char out[], int len, int newline_flag)
{
   int idx,idx2,blks,left_over;
   // Since 3 input bytes = 4 output bytes, figure out how many even sets of 3 input bytes
   // there are and process those. Multiplying by the equivilent of 3/3 (int arithmetic)
   // will reduce a number to the lowest multiple of 3.
   blks = (len / 3) * 3;
   for (idx=0,idx2=0; idx < blks; idx += 3,idx2 += 4) {
      out[idx2] = charset[in[idx] >> 2];
      out[idx2+1] = charset[((in[idx] & 0x03) << 4) + (in[idx+1] >> 4)];
      out[idx2+2] = charset[((in[idx+1] & 0x0f) << 2) + (in[idx+2] >> 6)];
      out[idx2+3] = charset[in[idx+2] & 0x3F];
      // The offical standard requires insertion of a newline every 76 chars
      if (!(idx2 % 77) && newline_flag) {
         out[idx2+4] = '\n';
         idx2++;
      }
   }
   left_over = len % 3;
   if (left_over == 1) {
      out[idx2] = charset[in[idx] >> 2];
      out[idx2+1] = charset[(in[idx] & 0x03) << 4];
      out[idx2+2] = '=';
      out[idx2+3] = '=';
      idx2 += 4;
   }
   else if (left_over == 2) {
      out[idx2] = charset[in[idx] >> 2];
      out[idx2+1] = charset[((in[idx] & 0x03) << 4) + (in[idx+1] >> 4)];
      out[idx2+2] = charset[(in[idx+1] & 0x0F) << 2];
      out[idx2+3] = '=';
      idx2 += 4;
   }
   out[idx2] = '\0';
   return(idx2);
}

/*
ADD: Option to strip out newlines
*/
int base64_decode(unsigned char in[], unsigned char out[], int len)
{
   int idx,idx2,blks,left_over;

   if (in[len-1] == '=')
      len--;
   if (in[len-1] == '=')
      len--;

   blks = (len / 4) * 4;
   for (idx=0,idx2=0; idx2 < blks; idx += 3,idx2 += 4) {
      out[idx] = (revchar(in[idx2]) << 2) + ((revchar(in[idx2+1]) & 0x30) >> 4);
      out[idx+1] = (revchar(in[idx2+1]) << 4) + (revchar(in[idx2+2]) >> 2);
      out[idx+2] = (revchar(in[idx2+2]) << 6) + revchar(in[idx2+3]);
   }
   left_over = len % 4;
   if (left_over == 2) {
      out[idx] = (revchar(in[idx2]) << 2) + ((revchar(in[idx2+1]) & 0x30) >> 4);
      out[idx+1] = (revchar(in[idx2+1]) << 4);
      idx += 2;
   }
   else if (left_over == 3) {
      out[idx] = (revchar(in[idx2]) << 2) + ((revchar(in[idx2+1]) & 0x30) >> 4);
      out[idx+1] = (revchar(in[idx2+1]) << 4) + (revchar(in[idx2+2]) >> 2);
      out[idx+2] = revchar(in[idx2+2]) << 6;
      idx += 3;
   }
   out[idx] = '\0';
   return(idx);
}

// koliko ce se znakova dobiti kada se kriptuje
uint16_t xtea_crypted_size(uint16_t len)
{
	 uint8_t crypted_size = 0;
	 crypted_size = len / 8;
	 crypted_size += len % 8 != 0 ? 1 : 0;
	 crypted_size *= 8;

	 return crypted_size + 8;
}

// koliko ce se znakova dobiti u base64 encoding-u
int xtea_base64_size(int n) {
	return ((n * 4) / 3) + (n / 96) + 6;
}

// koliko ce se znakova dobiti kada se vrati iz base64 encoding-a
int xtea_plain_size(int n) {
	return (( 32*n -192 ) / 43) + 1;
}


#if defined(POLARSSL_CIPHER_MODE_CBC)
/*
 * XTEA-CBC buffer encryption/decryption
 */
int xtea_crypt_cbc( xtea_context *ctx, int mode, size_t length,
                    unsigned char iv[8], const unsigned char *input,
                    unsigned char *output)
{
    int i;
    unsigned char temp[8];

    if( length % 8 )
        return( POLARSSL_ERR_XTEA_INVALID_INPUT_LENGTH );

    if( mode == XTEA_DECRYPT )
    {
        while( length > 0 )
        {
            memcpy( temp, input, 8 );
            xtea_crypt_ecb( ctx, mode, input, output );

            for( i = 0; i < 8; i++ )
                output[i] = (unsigned char)( output[i] ^ iv[i] );

            memcpy( iv, temp, 8 );

            input  += 8;
            output += 8;
            length -= 8;
        }
    }
    else
    {
        while( length > 0 )
        {
            for( i = 0; i < 8; i++ )
                output[i] = (unsigned char)( input[i] ^ iv[i] );

            xtea_crypt_ecb( ctx, mode, output, output );
            memcpy( iv, output, 8 );

            input  += 8;
            output += 8;
            length -= 8;
        }
    }

    return( 0 );
}
#endif /* POLARSSL_CIPHER_MODE_CBC */
#endif /* !POLARSSL_XTEA_ALT */

#if defined(POLARSSL_SELF_TEST)

#include <string.h>
#include <stdio.h>

/*
 * XTEA tests vectors (non-official)
 */

static const unsigned char xtea_test_key[6][16] =
{
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
     0x0c, 0x0d, 0x0e, 0x0f },
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
     0x0c, 0x0d, 0x0e, 0x0f },
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
     0x0c, 0x0d, 0x0e, 0x0f },
   { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00 },
   { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00 },
   { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00 }
};

static const unsigned char xtea_test_pt[6][8] =
{
    { 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48 },
    { 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41 },
    { 0x5a, 0x5b, 0x6e, 0x27, 0x89, 0x48, 0xd7, 0x7f },
    { 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48 },
    { 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41 },
    { 0x70, 0xe1, 0x22, 0x5d, 0x6e, 0x4e, 0x76, 0x55 }
};

static const unsigned char xtea_test_ct[6][8] =
{
    { 0x49, 0x7d, 0xf3, 0xd0, 0x72, 0x61, 0x2c, 0xb5 },
    { 0xe7, 0x8f, 0x2d, 0x13, 0x74, 0x43, 0x41, 0xd8 },
    { 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41 },
    { 0xa0, 0x39, 0x05, 0x89, 0xf8, 0xb8, 0xef, 0xa5 },
    { 0xed, 0x23, 0x37, 0x5a, 0x82, 0x1a, 0x8c, 0x2d },
    { 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41 }
};

/*
 * Checkup routine
 */
int xtea_self_test( int verbose )
{
    int i, ret = 0;
    unsigned char buf[8];
    xtea_context ctx;

    xtea_init( &ctx );
    for( i = 0; i < 6; i++ )
    {
        if( verbose != 0 )
            polarssl_printf( "  XTEA test #%d: ", i + 1 );

        memcpy( buf, xtea_test_pt[i], 8 );

        xtea_setup( &ctx, xtea_test_key[i] );
        xtea_crypt_ecb( &ctx, XTEA_ENCRYPT, buf, buf );

        if( memcmp( buf, xtea_test_ct[i], 8 ) != 0 )
        {
            if( verbose != 0 )
                polarssl_printf( "failed\n" );

            ret = 1;
            goto exit;
        }

        if( verbose != 0 )
            polarssl_printf( "passed\n" );
    }

    if( verbose != 0 )
        polarssl_printf( "\n" );

exit:
    xtea_free( &ctx );

    return( ret );
}

#endif /* POLARSSL_SELF_TEST */

#endif /* POLARSSL_XTEA_C */
