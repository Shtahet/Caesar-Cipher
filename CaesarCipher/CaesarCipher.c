#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


void *realloc(void *aptr, size_t bytes);
int find_key(int, int[]);

int main()
{
	int w = 600000, v = 0, ww = 60000;
	int n = 0, r = 0, f = 0, err = 0, g;
	int k = 0, ke, key = 0;
	char alp[52] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	char *a;
	char *b;
	b = (char*)malloc(w * sizeof(char));
	a = (char*)malloc(ww * sizeof(char));
	while (1) {
		scanf("%c", &a[n]);
		if (a[n] == '\n' || a[n] == EOF) {
			break;
		}
		if (a[n] < 'A' || a[n] > 'z' || (a[n] > 'Z' && a[n] < 'a'))
		{ 
			err = 1; 
		}
		n += 1;
		if (n == w) { w = w * 2; a = (char*)realloc(a, w * sizeof(char)); }
	}
	w = 1;
	while (1) {
		scanf("%c", &b[k]);
		if (b[k] == '\n' || b[k] == EOF) {
			break;
		}
		if (b[k] < 64 || b[k] > 123 || (b[k] > 90 && b[k] < 97)) { err = 1; }
		k += 1;
		if (k == w) { w = w * 2; b = (char*)realloc(b, w * sizeof(char)); }
	}
	if (err == 1) { fprintf(stderr, "Error: Chybny vstup!\n"); r = 100; }
	else if (k != n) { fprintf(stderr, "Error: Chybna delka vstupu!\n"); r = 101; }
	else {
		int* array = (int*)malloc(n * sizeof(int));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 52; j++) {
				if (a[i] == alp[j])  g = j;
				if (b[i] == alp[j]) f = j;
			}
			ke = f - g;
			array[i] = ke;
		}
		if (n == 1) { printf("%c", b[0]); }
		else {
			key = find_key(n, array);
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < 52; j++) {
					v = j + key;
					if (v < 0)v = v + 52;
					if (v >= 52)v = v - 52;
					if (a[i] == alp[j]) printf("%c", alp[v]);
				}
			}
		}
	}
	free(a);
	a = NULL;
	free(b);
	b = NULL;
	if (err == 0 && k == n)printf("\n");
	return r;
}

int find_key(int size, int  x[]) {
	int k, i, j, r = 0, z = 1;
	for (i = 0; i < size - 1; i++) {
		for (j = i + 1; j < size; j++) {
			if (x[i] == x[j]) {
				r += 1;
				if (z < r)z = r;
			}
		}r = 0;
	}
	for (i = 0; i < size - 1; i++) {
		for (j = i + 1; j < size; j++) {
			if (x[i] == x[j]) {
				r += 1;
				if (r == z)k = x[i];
			}
		}
	}
	return k;
}