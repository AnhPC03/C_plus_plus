#include <iostream>
#include <fstream>
#include <chrono>
#include <string.h>

using namespace std;
using namespace std::chrono;

void naiveStringSearch(char *text, char *searchString) {
    long size1 = strlen(text);
    long size2 = strlen(searchString);
    long i, j;
    int count;
    for (i = 0; i < size1-size2; ++i) {
        for (j = 0; j < size2; ++j) {
            if (text[i + j] != searchString[j]) {
                break;
            }
            if (j == size2-1) {
                ++count;
            }
        }
    }
}

void searchRabinKarp(char *pat, char *txt, long q)
{
    int d = 256;
    long M = strlen(pat);
    long N = strlen(txt);
    long i, j;
    long p = 0;
    long t = 0;
    long h = 1;
    int count;
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;
    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }
    for (i = 0; i <= N - M; i++)
    {
        if ( p == t )
        {
            for (j = 0; j < M; j++)
            {
                if (txt[i+j] != pat[j])
                    break;
            }
            if (j == M)
                ++count;
        }
        if ( i < N-M )
        {
            t = (d*(t - txt[i]*h) + txt[i+M])%q;
            if (t < 0)
            t = (t + q);
        }
    }
}

void computeLPSArray(char* pat, long M, long* lps);
void KMPSearch(char* pat, char* txt)
{
    long M = strlen(pat);
    long N = strlen(txt);
    long lps[M];
    computeLPSArray(pat, M, lps);
    long i = 0;
    long j = 0;
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {
            j = lps[j - 1];
        }
        else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}


void computeLPSArray(char* pat, long M, long* lps)
{
    long len = 0;
    lps[0] = 0;
    long i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0) {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}


void badCharHeuristic(char *str, long size,
                        char *badchar)
{
    long i;
    for (i = 0; i < 256; i++)
        badchar[i] = -1;
    for (i = 0; i < size; i++)
        badchar[(long) str[i]] = i;
}
void searchBoyerMoore(char *txt, char *pat)
{
    long m = strlen(pat);
    long n = strlen(txt);
    char *badchar = new char[256];
    badCharHeuristic(pat, m, badchar);
    long s = 0;
    while(s <= (n - m))
    {
        long j = m - 1;
        while(j >= 0 && pat[j] == txt[s + j])
            j--;
        if (j < 0)
        {
            s += (s + m < n)? m-badchar[txt[s + m]] : 1;
        }
        else
            s += (1 > j - badchar[txt[s + j]]) ? 1 : (j - badchar[txt[s + j]]);
    }
}

int main()
{
    FILE *file;
    file = fopen("Data.txt", "r");
    if (file == NULL) {
        return -1;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *text = new char[length];
    long i = 0;
    while(fscanf(file, "%c", &text[i]) != EOF) {
        ++i;
    }
    fclose(file);
    cout << "tim kiem theo word\n";
            char *word = "she";
            auto start = high_resolution_clock::now();
            naiveStringSearch(text, word);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Thoi gian tim kiem word bang thuat toan Naive la: " << duration.count() << " micro giay\n\n";

            start = high_resolution_clock::now();
            searchRabinKarp(word, text, 101);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Thoi gian tim kiem word bang thuat toan Rabin-Karp la: " << duration.count() << " micro giay\n\n";

            start = high_resolution_clock::now();
            KMPSearch(word, text);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Thoi gian tim kiem word bang thuat toan KMP la: " << duration.count() << " micro giay\n\n";

            start = high_resolution_clock::now();
            searchBoyerMoore(text, word);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Thoi gian tim kiem word bang thuat toan Boyer Moore la: " << duration.count() << " micro giay\n\n";
    cout << "\ntim kiem theo sentence\n";
            char *sentence = "Asia Bibi has always maintained her innocence in a case that has polarised Pakistan.";
            start = high_resolution_clock::now();
            naiveStringSearch(text, sentence);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Thoi gian tim kiem sentence bang thuat toan Naive la: " << duration.count() << " micro giay\n\n";

            start = high_resolution_clock::now();
            searchRabinKarp(sentence, text, 101);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Thoi gian tim kiem sentence bang thuat toan Rabin-Karp la: " << duration.count() << " micro giay\n\n";

            start = high_resolution_clock::now();
            KMPSearch(sentence, text);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Thoi gian tim kiem sentence bang thuat toan KMP la: " << duration.count() << " micro giay\n\n";

            start = high_resolution_clock::now();
            searchBoyerMoore(text, sentence);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Thoi gian tim kiem sentence bang thuat toan Boyer Moore la: " << duration.count() << " micro giay\n\n";
    cout << "\ntim kiem theo paragraph\n";
            char *paragraph = "Islam is Pakistan's national religion and underpins its legal system. Public support for the strict blasphemy laws is strong. Hardline politicians have often backed severe punishments, partly as a way of shoring up their support base.";
            start = high_resolution_clock::now();
            naiveStringSearch(text, paragraph);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Thoi gian tim kiem paragraph bang thuat toan Naive la: " << duration.count() << " micro giay\n\n";

            start = high_resolution_clock::now();
            searchRabinKarp(paragraph, text, 101);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Thoi gian tim kiem paragraph bang thuat toan Rabin-Karp la: " << duration.count() << " micro giay\n\n";

            start = high_resolution_clock::now();
            KMPSearch(paragraph, text);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Thoi gian tim kiem paragraph bang thuat toan KMP la: " << duration.count() << " micro giay\n\n";

            start = high_resolution_clock::now();
            searchBoyerMoore(text, paragraph);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Thoi gian tim kiem paragraph bang thuat toan Boyer Moore la: " << duration.count() << " micro giay\n\n";
    return 0;
}
