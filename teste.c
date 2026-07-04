#include <gtk/gtk.h>

static void abrir_janela(GtkApplication *app, gpointer user_data) {
    GtkWidget *janela;

    janela = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(janela), "Minha Primeira Janela GTK4");
    gtk_window_set_default_size(GTK_WINDOW(janela), 400, 300);

    // No GTK4 mudou aqui: não usamos mais 'gtk_widget_show_all'.
    // Usamos 'gtk_window_present' para exibir a janela.
    gtk_window_present(GTK_WINDOW(janela));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.escola.janela", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(abrir_janela), NULL);
    
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}