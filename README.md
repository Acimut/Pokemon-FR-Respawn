# Pokemon FR Respawn
 Personaliza el respawn luego de perder.


***Notas:***

- DevkitARM y ARMIPS son necesarios.

- Para compilar es necesario tener preproc.exe dentro alguna ruta de la variable PATH

- Abrir el archivo config.mk, buscar y cambiar ff0000 de la siguiente línea por un offset alineado con suficiente espacio libre:
        `INSERT_INTO ?= 0x08ff0000`

- Compilan ejecutando make con su terminal, y una rom con la inyección aparecerá en una carpeta llamada build.

- Archivos dentro de la carpeta `include` fueron tomados de [**pokefirered**](https://github.com/pret/pokefirered).

