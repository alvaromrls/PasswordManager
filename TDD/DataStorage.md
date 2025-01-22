- [x] **Constructor** :Crear una instancia de `DataStorage` con una ruta válida.
      _Verificar_ : No se lanza ninguna excepción.
- [x] **Carga de datos básicos** :Cargar un archivo JSON inexistente.
      _Verificar_ : Retorna un JSON vacío o crea un archivo nuevo vacío.
- [x] **Guardado de datos básicos** :
  - [x] Guardar un objeto JSON en un archivo.
        _Verificar_ : El archivo existe y contiene el JSON guardado.
- [ ] **Carga de datos desde un archivo existente** :
  - [ ] Cargar un archivo JSON previamente guardado.
        _Verificar_ : Los datos coinciden con lo esperado.
- [x] **Comprobar existencia de un usuario** :Verificar si un usuario existe en un JSON vacío.
      _Verificar_ : Devuelve `false`.
- [x] **Añadir un usuario nuevo** :
  - [x] Guardar datos para un usuario que no existía.
        _Verificar_ : El usuario ahora existe en el archivo.
- [x] **Comprobar existencia de un usuario inexistente** :
  - [x] Verificar si un usuario añadido no está presente.
        _Verificar_ : Devuelve `false`.
- [x] **Cargar datos de un usuario existente** :
  - [ ] Obtener los datos de un usuario que existe en el archivo.
        _Verificar_ : Los datos cargados coinciden con lo esperado.
- [x] **Actualizar datos de un usuario existente** :
  - [ ] Guardar nuevos datos para un usuario que ya existe.
        _Verificar_ : Los datos actualizados se reflejan correctamente en el archivo.
- [ ] **Eliminar un usuario existente** :
  - [ ] Borrar un usuario del archivo.
        _Verificar_ : El usuario ya no está presente en el archivo.
- [ ] **Eliminar un usuario inexistente** :
  - [ ] Intentar eliminar un usuario que no existe.
        _Verificar_ : No ocurre ningún cambio o error.
