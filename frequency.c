/* ===========================================================================
 * Header-Dateien einbinden
 * ======================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "frequency.h"


/* ===========================================================================
 * Makros
 * ======================================================================== */

/**
 * Makro zur Prüfung ob die Speicherallokation erfolgreich war: Ist die
 * übergebene Variable NULL, wird das Programm mit einer Fehlermeldung
 * abgebrochen.
 */
#define ASSERT_NOT_NULL(VAR) \
{if (VAR == NULL) { \
    fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno));\
    exit(EXIT_FAILURE); \
}}

/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */


/* ---------------------------------------------------------------------------
 * Funktion: frequency_create
 * ------------------------------------------------------------------------ */
extern FREQUENCY *frequency_create(const unsigned char word, const int count)
{
    /* Speicher für die Struktur allokieren */
    FREQUENCY *p_frequency = malloc(sizeof (FREQUENCY));
    ASSERT_NOT_NULL(p_frequency);

    /* Komponenten der Struktur initialisieren */
    p_frequency->word = '\0';
    p_frequency->count = count;
    frequency_set_word(p_frequency, word);

    return p_frequency;
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_destroy
 * ------------------------------------------------------------------------ */
extern void frequency_destroy(FREQUENCY **pp_frequency)
{
    if (pp_frequency != NULL && *pp_frequency != NULL)
    {

#ifdef DEBUG
        /* Ausgabe der zu löschenden Daten zu Debugzwecken */
        printf("- Loesche struct Frequency ");
        frequency_print(*pp_frequency);
        printf(" \n");
#endif

        free(*pp_frequency);
        *pp_frequency = NULL;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_get_word
 * ------------------------------------------------------------------------ */
extern unsigned char frequency_get_word(const FREQUENCY *p_frequency)
{
    if (p_frequency != NULL)
    {
        return p_frequency->word;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_get_count
 * ------------------------------------------------------------------------ */
extern int frequency_get_count(const FREQUENCY *p_frequency)
{
    int count = -1;

    if (p_frequency != NULL)
    {
        count = p_frequency->count;
    }

    return count;
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_set_word
 * ------------------------------------------------------------------------ */
extern void frequency_set_word(FREQUENCY *p_frequency, 
                               const unsigned char word)
{
    if (p_frequency != NULL)
    {
        p_frequency->word = word;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_set_count
 * ------------------------------------------------------------------------ */
extern void frequency_set_count(FREQUENCY *p_frequency, 
                                const int count)
{
    if (p_frequency != NULL)
    {
        p_frequency->count = count;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_compare
 * ------------------------------------------------------------------------ */
extern int frequency_compare(const FREQUENCY *p_frequency1,
        const FREQUENCY *p_frequency2)
{
    if (p_frequency1 != NULL && p_frequency2 != NULL)
    {
        return (p_frequency1->count == p_frequency2->count 
                && p_frequency1->word == p_frequency2->word) ? 0 : 1;
    }
    else 
    {
        return 1;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_get_string
 * ------------------------------------------------------------------------ */
extern char *frequency_get_string(const FREQUENCY *p_frequency)
{
    char *string;
    
    string = malloc(sizeof(char));
    strcpy(string, "");

    if (p_frequency != NULL)
    {
        /* Anzahl Stellen von count berechnen */
        int arity = 1;
        while (arity * 10 < p_frequency->count) 
        {
            arity++;
        }
        /* Inhalt der Struktur in String schreiben */
        if (p_frequency->word != '\0')
        {
            printf("[%c: %d]",
                     p_frequency->word, p_frequency->count);
        }
        else
        {
            snprintf(string, arity + 5 * sizeof(char),
                     "[-: %d]", p_frequency->count);
        }
    }

    return string;
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_print
 * ------------------------------------------------------------------------ */
extern void frequency_print(const FREQUENCY *p_frequency)
{
    if (p_frequency != NULL)
    {
        printf("[%c: %d]", p_frequency->word, p_frequency->count);
    }
}
