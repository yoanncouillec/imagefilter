# ImageFilter

ImageFilter is a C library that applies transformation to images like negative, rotate, blur, etc.

* **Easy:** Say what transformation you want on what image and apply!
* **Flexible:** You can mix transformations.
* **Clear:** You know exactly what's going on.

## Examples

```c
  source = charger_image_pgm(source_name);
  destination = negatif(source);
  destination = rotation_droite (destination, angle);
  sauver_image_pgm(destination_name, destination);
```

This example applies successively a negative transformation and a rotation.

## Installation

Include the library in your C code:

## License

ImageFilter is made under the terms of the MIT license.