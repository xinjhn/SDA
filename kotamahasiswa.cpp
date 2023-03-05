#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mahasiswaNode {
    char nama_mahasiswa[50];
    struct mahasiswaNode* next;
} mahasiswaNode;

typedef struct KotaNode {
    char nama_kota[50];
    struct KotaNode* next;
    struct mahasiswaNode* mahasiswa;
} KotaNode;

KotaNode* head_kota = NULL;

void addKota(char nama_kota[]);
void addMahasiswa(char nama_kota[], char nama_mahasiswa[]);
void deleteKota(char nama_kota[]);
void deleteMahasiswa(char nama_kota[], char nama_mahasiswa[]);
void printKota();

int main() {
	addKota("Jakarta");
	addKota("Bandung");
	addKota("Surabaya");
	addMahasiswa("Jakarta", "Budi");
	addMahasiswa("Jakarta", "Ani");
	addMahasiswa("Bandung", "Cindy");

	deleteMahasiswa("Jakarta", "Budi");
	deleteKota("Surabaya");

	printKota();

	return 0;
}

void addKota(char nama_kota[]) {
    KotaNode* new_kota = (KotaNode*)malloc(sizeof(KotaNode));
    strcpy(new_kota->nama_kota, nama_kota);
    new_kota->mahasiswa = NULL;
    new_kota->next = head_kota;
    head_kota = new_kota;
    printf("Kota %s berhasil ditambahkan\n", nama_kota);
}


void addMahasiswa(char nama_kota[], char nama_mahasiswa[]) {
    KotaNode* current_kota = head_kota;
    while (current_kota != NULL) {
        if (strcmp(current_kota->nama_kota, nama_kota) == 0) {
            mahasiswaNode* new_mahasiswa = (mahasiswaNode*)malloc(sizeof(mahasiswaNode));
            strcpy(new_mahasiswa->nama_mahasiswa, nama_mahasiswa);
            new_mahasiswa->next = current_kota->mahasiswa;
            current_kota->mahasiswa = new_mahasiswa;
            printf("Mahasiswa %s berhasil ditambahkan pada kota %s\n", nama_mahasiswa, nama_kota);
            return;
        }
        current_kota = current_kota->next;
    }
    printf("Kota dengan nama %s tidak ditemukan\n", nama_kota);
}

void deleteKota(char nama_kota[]) {
    KotaNode* current_kota = head_kota;
    KotaNode* prev_kota = NULL;
    while (current_kota != NULL) {
        if (strcmp(current_kota->nama_kota, nama_kota) == 0) {
            if (prev_kota == NULL) {
                head_kota = current_kota->next;
            }
            else {
                prev_kota->next = current_kota->next;
            }
            free(current_kota);
            printf("Kota %s berhasil dihapus\n", nama_kota);
            return;
        }
        prev_kota = current_kota;
        current_kota = current_kota->next;
    }
    printf("Kota dengan nama %s tidak ditemukan\n", nama_kota);
}

void deleteMahasiswa(char nama_kota[], char nama_mahasiswa[]) {
    KotaNode* current_kota = head_kota;
    while (current_kota != NULL) {
        if (strcmp(current_kota->nama_kota, nama_kota) == 0) {
            mahasiswaNode* current_mahasiswa = current_kota->mahasiswa;
            mahasiswaNode* prev_mahasiswa = NULL;
            while (current_mahasiswa != NULL) {
                if (strcmp(current_mahasiswa->nama_mahasiswa, nama_mahasiswa) == 0) {
                    if (prev_mahasiswa == NULL) {
                        current_kota->mahasiswa = current_mahasiswa->next;
                    }
                    else {
                        prev_mahasiswa->next = current_mahasiswa->next;
                    }
                    free(current_mahasiswa);
                    printf("mahasiswa %s berhasil dihapus dari kota %s\n", nama_mahasiswa, nama_kota);
                    return;
                }
                prev_mahasiswa = current_mahasiswa;
				current_mahasiswa = current_mahasiswa->next;
			}
			printf("mahasiswa dengan nama %s tidak ditemukan pada kota %s\n", nama_mahasiswa, nama_kota);
			return;
		}
		current_kota = current_kota->next;
	}
	printf("Kota dengan nama %s tidak ditemukan\n", nama_kota);
}

void printKota() {
	KotaNode* current_kota = head_kota;
	while (current_kota != NULL) {
		printf("%s\n", current_kota->nama_kota);
		mahasiswaNode* current_mahasiswa = current_kota->mahasiswa;
		while (current_mahasiswa != NULL) {
			printf(" - %s\n", current_mahasiswa->nama_mahasiswa);
			current_mahasiswa = current_mahasiswa->next;
		}
	current_kota = current_kota->next;
	}
}

