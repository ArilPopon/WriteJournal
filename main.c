#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Fungsi untuk menghitung jumlah kata berdasarkan spasi
int countWords(char *str)
{
    int count = 0, i = 0;
    while (str[i])
    {
        if (isspace(str[i]))
            count++;
        i++;
    }
    return count + 1; // Jumlah kata adalah jumlah spasi + 1
}

// Fungsi untuk menghitung jumlah kata berdasarkan koma (untuk kata kunci)
int countKeywords(char *str)
{
    int count = 1, i = 0; // Mulai dari 1 karena tidak ada koma di awal
    while (str[i])
    {
        if (str[i] == ',')
            count++;
        i++;
    }
    return count;
}

// Fungsi untuk memvalidasi email
int validateEmail(char *email)
{
    int len = strlen(email);
    char *domain = strstr(email, ".ac.id");

    // Cek apakah domain email benar
    if (!domain || strcmp(domain, ".ac.id") != 0)
        return 0;

    // Cek apakah ada karakter '@' sebelum domain
    for (int i = 0; i < len - 6; i++)
    {
        if (email[i] == '@')
            return 1;
    }
    return 0;
}

// Fungsi untuk menampilkan hasil akhir jurnal
void showJurnal(char *title, char *authors, char *affiliation, char *email, char *abstract, char *keywords)
{
    char journal[5000];
    snprintf(journal, sizeof(journal),
             "%s\n\n%s\n%s\n%s\n\n%s\n\nKata Kunci: %s\n",
             title, authors, affiliation, email, abstract, keywords);

    // Output hasil akhir
    printf("\n%s", journal);
}

// Fungsi utama untuk WriteJournal
void writeJournal()
{
    char title[100], authors[100], affiliation[100], email[100], abstract[2500], keywords[100];

    // Input Judul
    printf("Masukkan Judul (5-14 kata):\n");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0; // Menghapus newline
    if (countWords(title) < 5 || countWords(title) > 14)
    {
        printf("Judul harus terdiri dari 5 hingga 14 kata.\n");
        return;
    }

    // Input Nama Penulis
    printf("Masukkan Nama Penulis (maksimal 3, dipisahkan dengan koma):\n");
    fgets(authors, sizeof(authors), stdin);
    authors[strcspn(authors, "\n")] = 0;      // Menghapus newline
    int authorCount = countKeywords(authors); // Gunakan koma sebagai pemisah
    if (authorCount > 3)
    {
        printf("Maksimal 3 penulis diperbolehkan.\n");
        return;
    }

    // Input Afiliasi
    printf("Masukkan Afiliasi:\n");
    fgets(affiliation, sizeof(affiliation), stdin);
    affiliation[strcspn(affiliation, "\n")] = 0; // Menghapus newline

    // Input Emailaba
    printf("Masukkan Email:\n");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0; // Menghapus newline
    if (!validateEmail(email))
    {
        printf("Email tidak valid\n. contoh : student@upnjatim.ac.id\n");
        return;
    }

    // Input Abstrak
    printf("Masukkan Abstrak (maksimal 200 kata):\n");
    fgets(abstract, sizeof(abstract), stdin);
    abstract[strcspn(abstract, "\n")] = 0; // Menghapus newline
    if (countWords(abstract) > 200)
    {
        printf("Abstrak tidak boleh lebih dari 200 kata. Anda memasukkan %d kata.\n", countWords(abstract));
        return;
    }

    // Input Kata Kunci
    printf("Masukkan Kata Kunci (3-5 kata, dipisahkan dengan koma):\n");
    fgets(keywords, sizeof(keywords), stdin);
    keywords[strcspn(keywords, "\n")] = 0;      // Menghapus newline
    int keywordCount = countKeywords(keywords); // Menghitung jumlah kata kunci berdasarkan koma
    if (keywordCount < 3 || keywordCount > 5)
    {
        printf("Kata kunci harus terdiri dari 3 hingga 5 kata.\n");
        return;
    }

    // Setelah input selesai, tampilkan jurnal
    showJurnal(title, authors, affiliation, email, abstract, keywords);
}

int main()
{
    writeJournal();
    return 0;
}
