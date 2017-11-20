# Computação Gráfica - Trabalho de Implementação 5

Universidade Federal de Goiás
Instituto de Informática
Caíque Araújo Spósito - 201202953


A estava tendo problemas com valores negativos quando aplicava o ponto de fuga em Z, neste caso, empurrei todas coordenadas de Z pra valores positivos, não sendo possível afastar o objeto (durante a perspectiva que tenha ponto de fuga em Z) em valores de Z negativos.

---------------
A Biblioteca SDL2_TTF está localmente no projeto pois em alguns laboratórios da UFG (principalmente os dos centros de aulas) possuem a SDL2 instalada porém não possuem a SDL2_TTF instalada. 

Se seu computador não possuir a biblioteca instalada, você irá conseguir compilar o projeto com o Make normalmente, porém ao executar o binário, um acontecerá um erro, dizendo que não foi possível carregar a biblioteca libSDL2_ttf, então é necessário a execução dos seguintes comandos no terminal para dizer onde está localizada (atente-se ao PATH da biblioteca, provavelmente é necessário a atualização):

```
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/aluno/CG/vendor/SDL2_ttf/lib
export LD_LIBRARY_PATH
```
