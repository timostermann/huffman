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
 * Strukturdefinitionen
 * ======================================================================== */

/**
 * Setzt Wörter mit einer Häufigkeit in Beziehung
 */
struct FREQUENCY
{
    /**
     * Komponente für das Wort
     */
    char *word;
    /**
     * Komponente für die Anzahl der Wortvorkommen
     */
    int count;
};


/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Funktion: frequency_create
 * ------------------------------------------------------------------------ */
extern struct FREQUENCY *frequency_create(const char *word, const int count)
{
    /* Speicher für die Struktur allokieren */
    struct FREQUENCY *p_frequency = malloc(sizeof (struct FREQUENCY));
    ASSERT_NOT_NULL(p_frequency);

    /* Komponenten der Struktur initialisieren */
    p_frequency->word = NULL;
    p_frequency->count = count;
    frequency_set_word(p_frequency, word);

    return p_frequency;
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_destroy
 * ------------------------------------------------------------------------ */
extern void frequency_destroy(struct FREQUENCY **pp_frequency)
{
    if (pp_frequency != NULL && *pp_frequency != NULL)
    {

#ifdef DEBUG
        /* Ausgabe der zu löschenden Daten zu Debugzwecken */
        printf("- Loesche struct Frequency ");
        frequency_print(*pp_frequency);
        printf(" \n");
#endif

        free((*pp_frequency)->word);  /* oder: free((**pp_frequency).word); */
        free(*pp_frequency);
        *pp_frequency = NULL;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_get_word
 * ------------------------------------------------------------------------ */
extern char *frequency_get_word(const struct FREQUENCY *p_frequency)
{
    char *copied_string = NULL;

    if (p_frequency != NULL && p_frequency->word != NULL)
    {
        /* Speicher für die Kopie allokieren */
        int word_length = (int) strlen(p_frequency->word);
        copied_string = malloc((word_length + 1) * sizeof (char));
        ASSERT_NOT_NULL(copied_string);

        strcpy(copied_string, p_frequency->word);
    }

    return copied_string;
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_get_count
 * ------------------------------------------------------------------------ */
extern int frequency_get_count(const struct FREQUENCY *p_frequency)
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
extern void frequency_set_word(struct FREQUENCY *p_frequency, 
                               const char *word)
{
    int word_length;

    if (p_frequency == NULL)
    {
        return;
    }

    /* Benötigten Speicherplatz abhängig vom übergebenen Wort ermitteln.
     * Wurde kein Wort angegeben, wird das alte Wort gelöscht. */
    if (word == NULL)
    {
        if (p_frequency->word != NULL)
        {
            free(p_frequency->word);
            p_frequency->word = NULL;
        }
    }
    else
    {
        word_length = (int) strlen(word);

        /* Speicher für das Wort allokieren */
        p_frequency->word =
                  (p_frequency->word == NULL)
                    ? malloc((word_length + 1) * sizeof (char))
                    : realloc(p_frequency->word,
                              (word_length + 1) * sizeof (char));
        ASSERT_NOT_NULL(p_frequency->word);

        /* Wort in die Struktur kopieren. */
        strcpy(p_frequency->word, word);
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_set_count
 * ------------------------------------------------------------------------ */
extern void frequency_set_count(struct FREQUENCY *p_frequency, 
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
extern int frequency_compare(const struct FREQUENCY *p_frequency1, 
        const struct FREQUENCY *p_frequency2)
{
    if (p_frequency1 != NULL && p_frequency2 != NULL
        && p_frequency1->word != NULL && p_frequency2->word != NULL) 
    {
        return (p_frequency1->count == p_frequency2->count 
                && (strcmp(p_frequency1->word, p_frequency2->word) == 0)) ? 0 : 1;
    }
    else 
    {
        return 1;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_get_string
 * ------------------------------------------------------------------------ */
extern char *frequency_get_string(const struct FREQUENCY *p_frequency)
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
        if (p_frequency->word != NULL)
        {
            size_t length = strlen(p_frequency->word) * sizeof(char)
                            + arity + 5 * sizeof(char);
            string = malloc(length);
            ASSERT_NOT_NULL(string);
            snprintf(string, length, "[%s: %d]", 
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
extern void frequency_print(const struct FREQUENCY *p_frequency)
{
    if (p_frequency != NULL  && p_frequency->word != NULL)
    {
        printf("[%s: %d]", p_frequency->word, p_frequency->count);
    }
}
