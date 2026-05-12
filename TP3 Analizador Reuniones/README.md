# TP3 - Analizador de Reuniones Grabadas

## Estructura del proyecto

```
TP3_AnalizadorReuniones/
├── TP3.pro
├── main.cpp
├── mainwindow.h / .cpp / .ui   ← Ventana principal con tabs
├── analizador.h / .cpp          ← Comunicación con OpenAI API
└── exportadorpdf.h / .cpp       ← Exportación a PDF con QPrinter
```

## Cómo abrir en Qt Creator

1. Abrí Qt Creator
2. File → Open File or Project → seleccioná `TP3.pro`
3. Compilá y ejecutá (Ctrl+R)

## Cómo usar la aplicación

1. **Ingresá el tema** de la reunión en el campo superior
2. **Ingresá tu API Key** de OpenAI (se oculta como contraseña)
3. **Cargá la transcripción**: botón "Cargar archivo" (.txt o .docx) o pegala directamente
4. **Hacé clic en "Analizar"** — el programa llama a GPT-4o y procesa la reunión
5. Los resultados aparecen en la pestaña "Resultados":
   - Resumen ejecutivo
   - Acta formal completa
   - Tareas por participante con plazos
6. **Exportá el PDF** con el botón verde

## Formato de la API Key

La API Key va en el campo de texto de la ventana (no está hardcodeada en el código).
Formato: `AIzaSy...`

Conseguís una en: https://aistudio.google.com/app/apikey

> Si tenés Google One AI Premium (Gemini Advanced), la misma cuenta te da acceso a la API de Gemini con cuota generosa.

## Notas técnicas

- Usa **Gemini 2.0 Flash** para el análisis (rápido y con contexto largo, ideal para transcripciones)
- Los archivos **.docx** se leen extrayendo el XML interno (requiere `unzip` instalado en el sistema)
- La exportación PDF usa **QPrinter + QTextDocument** (sin dependencias externas)
- El módulo `network` de Qt maneja la comunicación HTTPS con la API de Google
