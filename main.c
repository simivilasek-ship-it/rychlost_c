#include <stdio.h>

double rychlost_ms(double draha, double cas) {
    return draha / cas;
}

double rychlost_kmh(double draha, double cas) {
    return (draha / cas) * 3.6;
}

int main() {
    FILE *f = fopen("cisla.txt", "r");
    FILE *out = fopen("prevody.txt", "w");

    if (!f) {
        printf("Soubor cisla.txt nelze otevrit.\n");
        return 1;
    }

    double draha, cas;
    int poradi = 0;
    double soucet_drah = 0;
    int pocet = 0;
    int pocet_zapsanych = 0;

    printf("Proverka rychlost\n");


    printf("%-6s %-10s %-10s %-10s\n", "poradi", "draha", "cas", "rychlost");

    while (fscanf(f, "%lf %lf", &draha, &cas) == 2) {
        poradi++;
        pocet++;
        soucet_drah += draha;

        double v_ms = rychlost_ms(draha, cas);

        // Hezké zarovnání do sloupců
            printf("%-6d %-10.0f %-10.0f %-10.2f m/s\n",
            poradi, draha, cas, v_ms);

        if (v_ms > 10) {
            double v_kmh = rychlost_kmh(draha, cas);

            int km = draha / 1000;
            int m = (int)draha % 1000;
            int min = cas / 60;
            int s = (int)cas % 60;

            // Zarovnaný výstup do prevody.txt
            fprintf(out, "%-4d %3d km %4d m   %3d min %3d s   %8.2f km/h\n",
                    poradi, km, m, min, s, v_kmh);

            pocet_zapsanych++;
        }
    }

    double prumer = soucet_drah / pocet;

    printf("\nPrumerna delka drahy je %.2f metru.\n", prumer);
    printf("Ze souboru cisla.txt bylo precteno %d dvojic cisel.\n", pocet);
    printf("Soubor prevody.txt byl vytvoren.\n");

    fprintf(out, "\nDo souboru prevody.txt bylo zapsano %d dvojic cisel.\n",
            pocet_zapsanych);

    fclose(f);
    fclose(out);

    return 0;
}
