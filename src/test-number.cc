/*
 * Copyright © 2019  Ebrahim Byagowi
 *
 *  This is part of HarfBuzz, a text shaping library.
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that the
 * above copyright notice and the following two paragraphs appear in
 * all copies of this software.
 *
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
 * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN
 * IF THE COPYRIGHT HOLDER HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * THE COPYRIGHT HOLDER SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE COPYRIGHT HOLDER HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 */

#include "hb.hh"
#include "hb-number.hh"


int
main (int argc, char **argv)
{
  {
    const char str[] = "123";
    const char *pp = str;
    const char *end = str + 3;

    int pv;
    hb_always_assert (hb_parse_int (&pp, end, &pv));
    hb_always_assert (pv == 123);
    hb_always_assert (pp - str == 3);
    hb_always_assert (end - pp == 0);
    hb_always_assert (!*end);
  }

  {
    const char str[] = "123";
    const char *pp = str;
    const char *end = str + strlen (str);

    unsigned int pv;
    hb_always_assert (hb_parse_uint (&pp, end, &pv));
    hb_always_assert (pv == 123);
    hb_always_assert (pp - str == 3);
    hb_always_assert (end - pp == 0);
    hb_always_assert (!*end);
  }

  {
    const char str[] = "12F";
    const char *pp = str;
    const char *end = str + 3;

    unsigned int pv;
    hb_always_assert (hb_parse_uint (&pp, end, &pv, true, 16));
    hb_always_assert (pv == 0x12F);
    hb_always_assert (pp - str == 3);
    hb_always_assert (end - pp == 0);
    hb_always_assert (!*end);
  }

  {
    const char str[] = "12Fq";
    const char *pp = str;
    const char *end = str + 4;

    unsigned int pv;
    hb_always_assert (!hb_parse_uint (&pp, end, &pv, true, 16));
    hb_always_assert (hb_parse_uint (&pp, end, &pv, false, 16));
    hb_always_assert (pv == 0x12F);
    hb_always_assert (pp - str == 3);
    hb_always_assert (end - pp == 1);
    hb_always_assert (!*end);
  }

  {
    const char str[] = "-123";
    const char *pp = str;
    const char *end = str + 4;

    int pv;
    hb_always_assert (hb_parse_int (&pp, end, &pv));
    hb_always_assert (pv == -123);
    hb_always_assert (pp - str == 4);
    hb_always_assert (end - pp == 0);
    hb_always_assert (!*end);
  }

  {
    const char str[] = "123";
    const char *pp = str;
    hb_always_assert (ARRAY_LENGTH (str) == 4);
    const char *end = str + ARRAY_LENGTH (str);

    unsigned int pv;
    hb_always_assert (hb_parse_uint (&pp, end, &pv));
    hb_always_assert (pv == 123);
    hb_always_assert (pp - str == 3);
    hb_always_assert (end - pp == 1);
  }

  {
    const char str[] = "123\0";
    const char *pp = str;
    hb_always_assert (ARRAY_LENGTH (str) == 5);
    const char *end = str + ARRAY_LENGTH (str);

    unsigned int pv;
    hb_always_assert (hb_parse_uint (&pp, end, &pv));
    hb_always_assert (pv == 123);
    hb_always_assert (pp - str == 3);
    hb_always_assert (end - pp == 2);
  }

  {
    const char str[] = "123V";
    const char *pp = str;
    hb_always_assert (ARRAY_LENGTH (str) == 5);
    const char *end = str + ARRAY_LENGTH (str);

    unsigned int pv;
    hb_always_assert (hb_parse_uint (&pp, end, &pv));
    hb_always_assert (pv == 123);
    hb_always_assert (pp - str == 3);
    hb_always_assert (end - pp == 2);
  }

  {
    const char str[] = ".123";
    const char *pp = str;
    const char *end = str + ARRAY_LENGTH (str);

    double pv;
    hb_always_assert (hb_parse_double (&pp, end, &pv));
    hb_always_assert ((int) roundf (pv * 1000.) == 123);
    hb_always_assert (pp - str == 4);
    hb_always_assert (end - pp == 1);
  }

  {
    const char str[] = "0.123";
    const char *pp = str;
    const char *end = str + ARRAY_LENGTH (str) - 1;

    double pv;
    hb_always_assert (hb_parse_double (&pp, end, &pv));
    hb_always_assert ((int) roundf (pv * 1000.) == 123);
    hb_always_assert (pp - str == 5);
    hb_always_assert (end - pp == 0);
  }

  {
    const char str[] = "0.123e0";
    const char *pp = str;
    const char *end = str + ARRAY_LENGTH (str) - 1;

    double pv;
    hb_always_assert (hb_parse_double (&pp, end, &pv));
    hb_always_assert ((int) roundf (pv * 1000.) == 123);
    hb_always_assert (pp - str == 7);
    hb_always_assert (end - pp == 0);
  }

  {
    const char str[] = "123e-3";
    const char *pp = str;
    const char *end = str + ARRAY_LENGTH (str) - 1;

    double pv;
    hb_always_assert (hb_parse_double (&pp, end, &pv));
    hb_always_assert ((int) roundf (pv * 1000.) == 123);
    hb_always_assert (pp - str == 6);
    hb_always_assert (end - pp == 0);
  }

  {
    const char str[] = ".000123e+3";
    const char *pp = str;
    const char *end = str + ARRAY_LENGTH (str) - 1;

    double pv;
    hb_always_assert (hb_parse_double (&pp, end, &pv));
    hb_always_assert ((int) roundf (pv * 1000.) == 123);
    hb_always_assert (pp - str == 10);
    hb_always_assert (end - pp == 0);
  }

  {
    const char str[] = "-.000000123e6";
    const char *pp = str;
    const char *end = str + ARRAY_LENGTH (str) - 1;

    double pv;
    hb_always_assert (hb_parse_double (&pp, end, &pv));
    hb_always_assert ((int) roundf (pv * 1000.) == -123);
    hb_always_assert (pp - str == 13);
    hb_always_assert (end - pp == 0);

  }

  {
    const char str[] = "-1.23E-1";
    const char *pp = str;
    const char *end = str + ARRAY_LENGTH (str) - 1;

    double pv;
    hb_always_assert (hb_parse_double (&pp, end, &pv));
    hb_always_assert ((int) roundf (pv * 1000.) == -123);
    hb_always_assert (pp - str == 8);
    hb_always_assert (end - pp == 0);
  }

  return 0;
}
