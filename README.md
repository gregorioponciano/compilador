# 🚀 Meu Primeiro App GTK4 com Instalador Windows

Este projeto demonstra como criar uma interface gráfica moderna em C utilizando a biblioteca **GTK4**, compilando o código para um arquivo `.exe` e gerando um instalador automático para Windows de forma simples.

---

## 🛠️ Passo 1: Configurando o Ambiente (MSYS2)

Como o Windows não possui um compilador C nativo, usamos o **MSYS2** para instalar o compilador GCC e as bibliotecas do GTK4.

1. Baixe e instale o MSYS2 pelo site oficial: [msys2.org](https://msys2.org)
2. Avance nas telas de instalação padrão clicando em **Next/Avançar** até o fim.
3. No menu Iniciar do Windows, procure e abra o terminal específico chamado **MSYS2 UCRT64**.
4. Cole os comandos abaixo (um por um) e aperte Enter:

```bash
# Atualizar os pacotes do sistema (digite 'S' ou 'Y' se o terminal pedir confirmação)
pacman -Syu

# Instalar o compilador GCC e a ferramenta de configuração
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-pkgconf

# Instalar a biblioteca do GTK4
pacman -S mingw-w64-ucrt-x86_64-gtk4
```

---

## 💻 Passo 2: O Código Fonte (`teste.c`)

Este é o código em C que cria a nossa interface gráfica:

```c
#include <gtk/gtk.h>

static void abrir_janela(GtkApplication *app, gpointer user_data) {
    GtkWidget *janela;

    janela = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(janela), "Minha Primeira Janela GTK4");
    gtk_window_set_default_size(GTK_WINDOW(janela), 400, 300);

    // Exibe a janela na tela
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
```

---

## 📦 Passo 3: Compilando e Juntando as DLLs (Sem Erros)

Para evitar erros de "DLL não encontrada" ao abrir o programa fora do terminal, siga este processo exato:

1. Vá para a sua **Área de Trabalho**.
2. Clique com o botão direito, escolha **Novo** -> **Pasta** e dê o nome de `MeuPrograma`.
3. Abra o terminal **MSYS2 UCRT64** e execute os comandos abaixo na ordem:

```bash
# 1. Entrar na pasta que você acabou de criar na Área de Trabalho
cd ~/Desktop/MeuPrograma

# 2. Compilar o código gerando o executável dentro da pasta (ajuste o caminho do teste.c se necessário)
gcc ~/Desktop/teste.c -o programa.exe `pkg-config --cflags --libs gtk4`

# 3. O comando mágico que copia todas as DLLs necessárias automaticamente
cp /ucrt64/bin/*.dll . 2>/dev/null || true
```

Agora, ao olhar a pasta `MeuPrograma`, ela estará cheia de arquivos `.dll` e com o arquivo `programa.exe`. Você já pode abrir o programa clicando duas vezes nele!

---

## 🎁 Passo 4: Criando o Instalador Visual (.exe único)

Para transformar essa pasta cheia de arquivos em um único instalador profissional (igual aos jogos que você baixa da internet):

1. Baixe e instale a ferramenta gratuita **Inno Setup**: [Download Inno Setup](http://jrsoftware.org).
2. Abra o **Inno Setup Compiler** e clique na opção **Create a new script file using the Script Wizard** -> **OK**.
3. Clique em **Next** na tela de boas-vindas.
4. Na tela **Application Information**, mude o *Application name* para o nome do seu programa e clique em **Next**.
5. Na tela **Application Folder**, apenas clique em **Next**.
6. Na tela **Application Files** (Atenção máxima aqui):
   * Em *Application main executable file*, clique em **Browse...**, vá até a pasta `MeuPrograma` na Área de Trabalho e selecione o arquivo **`programa.exe`**.
   * Logo abaixo, clique no botão **Add folder...** e selecione a pasta **`MeuPrograma`** inteira. Clique em **Sim** na pergunta que aparecer na tela.
   * Clique em **Next**.
7. Vá clicando em **Next/Avançar** nas próximas telas sem alterar nada até clicar em **Finish**.
8. O programa perguntará: *"Do you want to compile the new script now?"*. Clique em **Sim**.
9. Escolha qualquer nome e salve o arquivo de script na Área de Trabalho.

Uma barra verde vai carregar no Inno Setup. Quando terminar, um arquivo chamado **`mysetup.exe`** (ou dentro de uma pasta chamada `Output`) estará pronto na sua Área de Trabalho! 

Este é o instalador final. Você pode apagar o resto e enviar apenas este arquivo para os seus amigos jogarem/testarem.

---
Feito com ❤️ por um estudante de programação.
