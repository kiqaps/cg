# Computação Gráfica - Trabalho de Implementação 4

Universidade Federal de Goiás
Instituto de Informática
Caíque Araújo Spósito - 201202953

A Biblioteca SDL2_TTF está localmente no projeto pois em alguns laboratórios da UFG (principalmente os dos centros de aulas) possuem a SDL2 instalada porém não possuem a SDL2_TTF instalada. 

Se seu computador não possuir a biblioteca instalada, você irá conseguir compilar o projeto com o Make normalmente, porém ao executar o binário, um acontecerá um erro, dizendo que não foi possível carregar a biblioteca libSDL2_ttf, então é necessário a execução dos seguintes comandos no terminal para dizer onde está localizada (atente-se ao PATH da biblioteca, provavelmente é necessário a atualização):

```
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/aluno/CG/vendor/SDL2_ttf/lib
export LD_LIBRARY_PATH
```
