/* -*- Mode: C; tab-width: 8;  indent-tabs-mode: nil; c-basic-offset: 8; c-brace-offset: -8; c-argdecl-indent: 8 -*- */
/* Copyright 2012 Dan Smith <dsmith@danplanet.com> */

#ifndef __UTIL_H
#define __UTIL_H

#define KPH_TO_MPH(km) (km * 0.621371192)
#define MS_TO_MPH(m) (m * 2.23693629)
#define M_TO_FT(m) (m * 3.2808399)
#define FT_TO_M(ft) (ft / 3.2808399)
#define C_TO_F(c) ((c * 9.0/5.0) + 32)
#define MM_TO_IN(mm) (mm * 0.0393700787)
#define KTS_TO_MPH(kts) (kts * 1.15077945)
#define KTS_TO_KPH(kts) (kts * 1.852)

#define STREQ(x,y) (strcmp(x, y) == 0)
#define STRNEQ(x,y,n) (strncmp(x, y, n) == 0)

#define HAS_BEEN(s, d) ((time(NULL) - s) > d)

#define PI 3.14159265
#define DEG2RAD(x) (x*(PI/180))
#define RAD2DEG(x) (x/(PI/180))

const char *CARDINALS[] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW" };

const char *direction(double degrees)
{
        return CARDINALS[((int)((degrees + 22.5) / 45.0)) % 8];
}

double get_direction(double fLng, double fLat, double tLng, double tLat)
{
        double rads;
        double result;

        fLng = DEG2RAD(fLng);
        fLat = DEG2RAD(fLat);
        tLng = DEG2RAD(tLng);
        tLat = DEG2RAD(tLat);

        rads = atan2(sin(tLng-fLng)*cos(tLat),
                     cos(fLat)*sin(tLat)-sin(fLat)*cos(tLat)*cos(tLng-fLng));

        result = RAD2DEG(rads);

        if (result < 0)
                return result + 360;
        else
                return result;
}

char *get_escaped_string(char *string)
{
        int i;
        char *escaped = NULL;
        int length = strlen(string) * 2 + 1;

        escaped = calloc(length, sizeof(char));

        /* Escape values */
        for (i = 0; i < strlen(string); i++) {
                if (strlen(escaped) + 6 >= length) {
                        char *tmp;
                        tmp = realloc(escaped, length * 2);
                        escaped = tmp;
                        length *= 2;
                }

                if (string[i] == '&')
                        strcat(escaped, "&amp;");
                else if (string[i] == '<')
                        strcat(escaped, "&lt;");
                else if (string[i] == '>')
                        strcat(escaped, "&gt;");
                else
                        strncat(escaped, &string[i], 1);
        }

        return escaped;
}

#endif
