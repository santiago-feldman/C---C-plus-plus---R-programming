/*
 * Lequel?
 *
 * Copyright (C) 2022 Marc S. Ressl
 *
 * Language identification based on trigrams.
 *
 * More info:
 * https://towardsdatascience.com/understanding-cosine-similarity-and-its-application-fd42f585296a
 *
 */

#include <cmath>
#include <codecvt>
#include <locale>
#include <iostream>
#include <ctype.h>

#include "Lequel.h"

#define MIN_LENGTH 3
#define MAX_LENGTH 1000

using namespace std;

/*
 * Builds a trigram profile for a given text.
 *
 * Parameters:
 * text - A list of lines (Text).
 *
 * Returns: the trigram profile.
 */
TrigramProfile buildTrigramProfile(const Text &text)
{
    // gets the text in a string
    wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    wstring unicodeString;
    for (auto &textLine : text)
    {
        if (textLine.length() >= MIN_LENGTH)
        {
            unicodeString += converter.from_bytes(textLine);
        }
    }

    map<string, float> textProfile;
    size_t length = unicodeString.length();
    if (length >= MIN_LENGTH)
    {
        //cuts the string to a suitable length to avoid a bottleneck
        if (length >= MAX_LENGTH)
        {
            length = MAX_LENGTH;
        }

        // gets the trigrams
        for (int i = 0; i <= length - 3; i++)
        {
            string trigram = "";
            wstring unicodeTrigram = &unicodeString.at(i);

            for (int j = 0; j < 3; j++)
            {
                trigram += converter.to_bytes(tolower(unicodeTrigram[j]));
            }
                       
            map<string, float>::iterator element;
            element = textProfile.find(trigram);

            if (element != textProfile.end())
            {
                element->second++;
            }
            else
            {
                textProfile.insert(pair<string, float>(trigram, 1));
            }
        }
    }

    return textProfile;
}

/*
 * Normalizes a trigram profile.
 *
 * Parameters:
 * trigramProfile - Trigram profile.
 */
void normalizeTrigramProfile(TrigramProfile &trigramProfile)
{
    map<string, float>::iterator element;
    float mod = 0.0f;

    // calculate module
    for (element = trigramProfile.begin(); element != trigramProfile.end(); element++)
    {
        mod += (element->second) * (element->second);
    }
    mod = sqrt(mod);

    // normalize
    for (auto &element : trigramProfile)
    {
        (&element)->second /= mod;
    }
}

/*
 * Calculates the cosine similarity between a text trigram profile
 * and a language trigram profile.
 *
 * Parameters:
 * textProfile - Text trigram profile.
 * languageProfile - Language trigram profile.
 *
 * Returns: the cosine similarity score.
 */
float getCosineSimilarity(TrigramProfile &textProfile, TrigramProfile &languageProfile)
{
    float similarity = 0.0f;

    for (auto &itText : textProfile)
    {
        std::map<string, float>::iterator itLang = languageProfile.find((&itText)->first);
        if (itLang != languageProfile.end())
        {
            similarity += ((&itText)->second) * (itLang->second);
        }
    }

    return similarity;
}

/*
 * Identifies the language of a text.
 *
 * Parameters:
 * text - A list of lines (Text).
 *
 * Returns: The language code of the most likely language.
 */
string identifyLanguage(const Text &text, Languages &languages)
{
    TrigramProfile textTrigram = buildTrigramProfile(text);
    normalizeTrigramProfile(textTrigram);

    std::string bestLanguage;
    float bestSim = 0.0f;

    for (auto &currentLanguage : languages)
    {
        float sim = getCosineSimilarity(textTrigram, (&currentLanguage)->trigramProfile);
        if (sim > bestSim)
        {
            bestLanguage = (&currentLanguage)->languageCode;
            bestSim = sim;
        }
    }

    return bestLanguage;
}
