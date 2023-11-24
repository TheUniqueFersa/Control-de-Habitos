al_init_primitives_addon(); //Iniciar la biblioteca de prmirtivas
al_install_keyboard(); //Iniciar el teclado
al_init_image_addon(); //Inciar el addon para imagenes



//AUDIO
al_install_audio(); //Iniciar el addon del audio
al_init_acodec_addon();
al_reserve_samples(n);

theme = al_load_sample("sonidos/theme.mp3"); // Carga un audio

//IMAGENES
al_load_bitmap("Imagenes/.PNG"); //carga una imagen para  un bitmap

//FUENTES
al_load_font("fuentes/Pixeled.ttf", 16, 0); //carga una fuenta


// VENTANA
al_set_window_title(disp, "COVI - Ventura por CLOVERS++"); //Pone nombre a una ventana
al_set_display_icon(disp, ICONO_C_V);//Le pone un icono a una ventana


timer_0_01 = al_create_timer(0.01); //Crea un timer
eventos = al_create_event_queue(); //Crea una cola de eventos en una variable de tipo cola de eventos

//REGISTRAR TIPOS DE EVENTOS
al_register_event_source(eventos, al_get_display_event_source(disp)); // FUENTE: eventos de la ventana
al_register_event_source(eventos, al_get_keyboard_event_source()); // FUENTE: eventos del teclado
al_register_event_source(eventos, al_get_timer_event_source(timer_0_01)); // FUENTE: eventos de tipo temporizador

al_start_timer(timer_0_01); //Inicializa un temporizador


//PARA ACABAR Y DESTRUIR TODO LO RELACIONDADO CON EVENTOS
al_destroy_display(disp);
al_destroy_timer(timer_0_01);
al_destroy_event_queue(eventos);

//color
ALLEGRO_COLOR color_fondo;

al_map_rgb(255, 255, 0); //Asignar color


al_clear_to_color(color_fondo); //Rellenar el disp con un color especifico


//Figuras primitivas
//Triangulo
al_draw_triangle(10, 10, 0, 100, 100, 50, al_map_rgb(255, 255, 0), 2);
al_draw_filled_triangle(10, 10, 0, 100, 100, 50, al_map_rgb(255, 255, 0));
//Rectagulo
al_draw_rectangle(30, 250, 150, 300, al_map_rgb(255, 0, 0), 3);
al_draw_filled_rectangle(30, 250, 150, 300, al_map_rgb(255, 0, 0));
//Rectangulo redondeado
al_draw_rounded_rectangle(30, 300, 300, 350, 4, 4, al_map_rgb(0, 0, 255), 2);
al_draw_filled_rounded_rectangle(30, 300, 300, 350, 4, 4, al_map_rgb(0, 0, 255));


//Elipse
al_draw_filled_ellipse(400, 300, 100, 200, al_map_rgb(200,0, 200));
//Circulo
al_draw_circle(500, 500, 100, al_map_rgb(120, 55, 255), 1);
//arco
al_draw_arc(300, 600, 100, 1, 2, al_map_rgb(255, 255, 0), 3);
//sector circular
al_draw_filled_pieslice(600, 600, 100, 1, 2, al_map_rgb(0, 255, 0));
al_draw_pieslice(600, 600, 100, 1, 2, al_map_rgb(255, 255, 255), 1);


//Poligono
float puntos[8] = {40, 200, 200, 100, 300, 411, 40, 300};

al_draw_polygon(puntos, 4, ALLEGRO_LINE_JOIN_ROUND, al_map_rgb(0, 0, 255), 5, 2);