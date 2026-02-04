#include <gtk/gtk.h>
#include "game.h"
#include "ui.h"

int main(int argc, char *argv[]){

    gtk_init(&argc, &argv);

    Game game;
    game_init(&game);

    ui_init(&game);

    gtk_main();

    return 0;
}