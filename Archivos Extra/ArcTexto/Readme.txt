Archivo de datos en texto

Breve reseña de los archivos de este paquete

1. LeerCar lee cada linea caracter a caracter en variable caracter.
2: LeerLinea lee por lineas completas en variable cadena.
3. LeerFormato lee de acuerdo a las componentes de cada linea en variables enteras o reales o de cadena o caracter o boolean según correspondan esos datos de texto.
4. LeerFormato2 utiliza freopen para reencauzar o redireccionar las entradas o salidas de los dispositivos por defecto de la consola, del teclado y la pantalla a archivos de texto, el comando cin lee en vez del teclado desde un archivo de texto, el indicado en el freopen y el comando cout graba en vez de la pantalla a un archivo de texto, también indicado por freopen.

Para abrir el archivo de texto con la facilidad freopen

 freopen(cadenaTexto,"r",stdin); hace que cin >> lee los datos desde el archivo indicado por cadenaTexto, la 'r' indica lectura y stdin indica el dispositivo de entrada.
 freopen(cadenaTexto,"w", stdout); hace que cout << graba los salida a un archivo de texto el indicado en cadenaTexto, la 'w' indica grabar y stdout indica el dispositivo de salida.

Para cerrar el archivo de texto con la facilidad freopen
 
 freopen("CON","r",stdin); para archivo de texto de lectura.
 freopen("CON","w",stdout); para archivo de texto de escritura.

