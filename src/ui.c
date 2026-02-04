#include <gtk/gtk.h>
#include <cairo.h>
#include <stdbool.h>
#include <math.h>

#include "ui.h"
#include "game.h"

#define CELL_SIZE 20
#define HEIGHT 20
#define WIDTH 20

static GtkWidget *drawing_area;
static GtkWidget *main_window;
static GtkWidget *score_label;
static Game *global_game;

/* Sprites */
static cairo_surface_t *fruit_sprite = NULL;
static cairo_surface_t *head_sprite  = NULL;

/* ------------------------------------------------ */
/* DESENHAR SPRITE COM ROTAÇÃO + ESCALA              */
/* ------------------------------------------------ */

static void draw_rotated_sprite(cairo_t *cr,
                                cairo_surface_t *sprite,
                                int x, int y,
                                double angle){

    int img_w = cairo_image_surface_get_width(sprite);
    int img_h = cairo_image_surface_get_height(sprite);

    double scale_x = (double)CELL_SIZE / img_w;
    double scale_y = (double)CELL_SIZE / img_h;

    cairo_save(cr);

    /* Centro da célula */
    cairo_translate(cr,
                    x * CELL_SIZE + CELL_SIZE / 2,
                    y * CELL_SIZE + CELL_SIZE / 2);

    /* Rodar */
    cairo_rotate(cr, angle);

    /* Escalar */
    cairo_scale(cr, scale_x, scale_y);

    /* Centrar sprite */
    cairo_translate(cr, -img_w / 2, -img_h / 2);

    cairo_set_source_surface(cr, sprite, 0, 0);
    cairo_paint(cr);

    cairo_restore(cr);
}

/* ------------------------------------------------ */
/* DESENHAR SPRITE ESCALADO (SEM ROTAÇÃO)            */
/* ------------------------------------------------ */

static void draw_scaled_sprite(cairo_t *cr,
                               cairo_surface_t *sprite,
                               int x, int y){

    int img_w = cairo_image_surface_get_width(sprite);
    int img_h = cairo_image_surface_get_height(sprite);

    double scale_x = (double)CELL_SIZE / img_w;
    double scale_y = (double)CELL_SIZE / img_h;

    cairo_save(cr);

    /* Move para a célula */
    cairo_translate(cr, x * CELL_SIZE, y * CELL_SIZE);

    /* Aplica escala */
    cairo_scale(cr, scale_x, scale_y);

    cairo_set_source_surface(cr, sprite, 0, 0);
    cairo_paint(cr);

    cairo_restore(cr);
}

/* ------------------------------------------------ */
/* POPUP GAME OVER                                  */
/* ------------------------------------------------ */

static void show_game_over_popup(){

    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(main_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Game Over!"
    );

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    /* Reiniciar jogo */
    game_restart(global_game);

    gtk_label_set_text(GTK_LABEL(score_label), "Score: 0");

    global_game->running = false;
    global_game->direction = 0;
}

/* ------------------------------------------------ */
/* DESENHO PRINCIPAL                                */
/* ------------------------------------------------ */

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data){

    Game *game = (Game *)data;

    /* ---------- FUNDO TRON ---------- */

    cairo_pattern_t *bg =
        cairo_pattern_create_linear(0, 0, 0, HEIGHT * CELL_SIZE);

    cairo_pattern_add_color_stop_rgb(bg, 0.0, 0.0, 0.0, 0.10);
    cairo_pattern_add_color_stop_rgb(bg, 1.0, 0.0, 0.0, 0.20);

    cairo_set_source(cr, bg);
    cairo_paint(cr);
    cairo_pattern_destroy(bg);

    /* Grelha neon */
    cairo_set_source_rgba(cr, 0.0, 0.8, 1.0, 0.15);
    cairo_set_line_width(cr, 1);

    for(int x = 0; x <= WIDTH; x++){
        cairo_move_to(cr, x * CELL_SIZE, 0);
        cairo_line_to(cr, x * CELL_SIZE, HEIGHT * CELL_SIZE);
    }

    for(int y = 0; y <= HEIGHT; y++){
        cairo_move_to(cr, 0, y * CELL_SIZE);
        cairo_line_to(cr, WIDTH * CELL_SIZE, y * CELL_SIZE);
    }

    cairo_stroke(cr);

    /* Glow central */
    cairo_pattern_t *glow = cairo_pattern_create_radial(
        WIDTH * CELL_SIZE / 2, HEIGHT * CELL_SIZE / 2, 30,
        WIDTH * CELL_SIZE / 2, HEIGHT * CELL_SIZE / 2, 300
    );

    cairo_pattern_add_color_stop_rgba(glow, 0.0, 0.0, 0.8, 1.0, 0.20);
    cairo_pattern_add_color_stop_rgba(glow, 1.0, 0.0, 0.0, 0.0, 0.0);

    cairo_set_source(cr, glow);
    cairo_paint(cr);
    cairo_pattern_destroy(glow);

    /* ---------- FRUTA (SPRITE ESCALADO) ---------- */

    draw_scaled_sprite(cr, fruit_sprite,
                       game->food.x,
                       game->food.y);

    /* ---------- CORPO (TRAIL NEON) ---------- */

    cairo_set_source_rgba(cr, 0.0, 0.9, 1.0, 0.85);

    for(int i = 0; i < game->snake.snakeTailLen; i++){

        int tx = game->snake.snakeTailX[i];
        int ty = game->snake.snakeTailY[i];

        cairo_rectangle(cr,
                        tx * CELL_SIZE,
                        ty * CELL_SIZE,
                        CELL_SIZE,
                        CELL_SIZE);

        cairo_fill(cr);
    }

    /* Glow extra */
    cairo_set_source_rgba(cr, 0.0, 0.8, 1.0, 0.20);

    for(int i = 0; i < game->snake.snakeTailLen; i++){

        int tx = game->snake.snakeTailX[i];
        int ty = game->snake.snakeTailY[i];

        cairo_rectangle(cr,
                        tx * CELL_SIZE - 2,
                        ty * CELL_SIZE - 2,
                        CELL_SIZE + 4,
                        CELL_SIZE + 4);

        cairo_fill(cr);
    }

    /* ---------- CABEÇA (SPRITE ROTATIVO ESCALADO) ---------- */

    double angle = 0;

    switch(game->direction){
        case 1: angle = M_PI;       break; /* esquerda */
        case 2: angle = 0;          break; /* direita */
        case 3: angle = -M_PI / 2;  break; /* cima */
        case 4: angle = M_PI / 2;   break; /* baixo */
        default: angle = 0;
    }

    draw_rotated_sprite(cr, head_sprite,
                        game->snake.x,
                        game->snake.y,
                        angle);

    return FALSE;
}

/* ------------------------------------------------ */
/* TECLADO                                          */
/* ------------------------------------------------ */

static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data){

    Game *game = (Game *)data;

    switch(event->keyval){

        case GDK_KEY_Left:
            if(game->direction != 2) game->direction = 1;
            game->running = true;
            break;

        case GDK_KEY_Right:
            if(game->direction != 1) game->direction = 2;
            game->running = true;
            break;

        case GDK_KEY_Up:
            if(game->direction != 4) game->direction = 3;
            game->running = true;
            break;

        case GDK_KEY_Down:
            if(game->direction != 3) game->direction = 4;
            game->running = true;
            break;

        case GDK_KEY_r:
            game_restart(game);
            game->running = false;
            game->direction = 0;
            break;

        case GDK_KEY_Escape:
            gtk_main_quit();
            break;
    }

    return TRUE;
}

/* ------------------------------------------------ */
/* QUIT BUTTON                                      */
/* ------------------------------------------------ */

static void on_quit_button_clicked(GtkButton *button, gpointer data){
    gtk_main_quit();
}

/* ------------------------------------------------ */
/* LOOP DO JOGO                                     */
/* ------------------------------------------------ */

static gboolean game_loop(gpointer data){

    Game *game = (Game *)data;

    if(game->running){

        game_update(game);

        if(!game->running){
            show_game_over_popup();
        }
    }

    /* Atualizar score */
    char text[50];
    sprintf(text, "Score: %d", game->score);
    gtk_label_set_text(GTK_LABEL(score_label), text);

    gtk_widget_queue_draw(drawing_area);

    return TRUE;
}

/* ------------------------------------------------ */
/* INIT UI                                          */
/* ------------------------------------------------ */

void ui_init(Game *game){

    global_game = game;

    /* Carregar sprites */
    fruit_sprite = cairo_image_surface_create_from_png("assets/fruit.png");
    head_sprite  = cairo_image_surface_create_from_png("assets/head.png");

    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_window), "Snake Tron");
    gtk_window_set_resizable(GTK_WINDOW(main_window), FALSE);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(main_window), vbox);

    /* Score */
    score_label = gtk_label_new("Score: 0");
    gtk_box_pack_start(GTK_BOX(vbox), score_label, FALSE, FALSE, 0);

    /* Área do jogo */
    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area,
                                WIDTH * CELL_SIZE,
                                HEIGHT * CELL_SIZE);

    gtk_box_pack_start(GTK_BOX(vbox), drawing_area, TRUE, TRUE, 0);

    /* Botão Quit */
    GtkWidget *quit_button = gtk_button_new_with_label("Quit");
    gtk_box_pack_start(GTK_BOX(vbox), quit_button, FALSE, FALSE, 0);

    /* Eventos */
    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw), game);
    g_signal_connect(main_window, "key-press-event", G_CALLBACK(on_key_press), game);
    g_signal_connect(quit_button, "clicked", G_CALLBACK(on_quit_button_clicked), NULL);

    /* Timer */
    g_timeout_add(150, game_loop, game);

    gtk_widget_show_all(main_window);
}