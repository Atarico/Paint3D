# Paint3D

Paint3D é uma aplicação Desktop desenvolvida em C++ com o framework gráfico Qt que permite o desenho de objetos tridimensionais utilizando Voxels. Atualmente, o único formato de arquivo suportado pela aplicação é `.off `.

## Pré-requisitos

É necessário o [Qt Creator](https://www.qt.io/download) com uma versão do Qt 5.12.2 ou superior para compilar o projeto (não garantimos retrocompatibilidade com versões anteriores).

## Instalação

Clone o repositório através do GitHub ou através do terminal:
```git
git clone https://github.com/Atarico/Paint3D.git
```

Após a clonagem, abra o arquivo Paint3D.pro com o Qt Creator e compile o projeto.

## Utilização

Após a compilação do projeto, basta executá-lo para interagir com a interface gráfica:

```diff
-Imagem de toda a aplicação-
```

### Novas Matrizes de Desenho

A aplicação inicia com uma matriz de desenho de 10x10x10 voxels. Mas o usuário pode iniciar uma nova matriz de desenho com outras dimensões em File>New 3D Canvas. **ATENÇÃO!** fazer isso irá permanentemente destruir qualquer matriz de desenho previamente em uso, incluindo seu conteúdo já desenhado, portanto recomendamos cuidado.

```diff
-Imagem do popup de nova matriz de desenho-
```

### Interface

Existem quatro telas no programa: 
+ 3D(topo esquerdo): é a tela 3D, onde você poderá ver em tempo real um _preview_ do que está sendo desenhado.
+ XY(topo direito): é a tela de desenho que representa os planos XY da sua matriz. Para alterar o plano atual, basta utilizar o slider ao lado, que representa o eixo Z.
+ XZ(base esquerda): é a tela de desenho que representa os planos XZ da sua matriz. Para alterar o plano atual, basta utilizar o slider ao lado, que representa o eixo Y.
+ YZ(base direita): é a tela de desenho que representa os planos YZ da sua matriz. Para alterar o plano atual, basta utilizar o slider ao lado, que representa o eixo X.


### Desenhando

Na barra de ferramentas existem 9 botões que são, da esquerda para a direita:

+ desenhar um voxel
+ apagar um voxel
+ desenhar um retângulo de voxels
+ apagar um retângulo de voxels 
+ desenhar uma esfera de voxels 
+ apagar uma esfera de voxels
+ desenhar uma elipsoide de voxels
+ apagar uma elipsoide de voxels
+ Salvar a escultura de voxels em um arquivo .OFF

Esses botões são a principal forma de interação com o ambiente tridimensional.

Para auxiliar o usuário, abaixo dos botões existe uma série de 3 displays com a posicao (X, Y, Z) do mouse em relação a sua matriz de desenho.

Ao lado dos displays, existe o selecionador de cor, onde o usuário pode selecionar a cor desejada tanto por meio dos quatro sliders RGBA, ou clicando no botão "color" para abrir o pop-up de seleção de cor.

```diff
-Imagem do popup de seleção de cor-
```

Ao lado do seletor de cores há os parâmetros para se desenhar um retângulo, esfera e elipse (lembre-se que os parâmetros servem tanto para os botões de desenhar quanto para os de apagar).
Com a cor e a ferramenta de desenho desejada selecionada, basta clicar e arrastar com o botão esquerdo em um dos três planos de desenho para começar a desenhar sua figura.

```diff
-Imagem de alguma figura desenhada-
```

### Salvando em formato .off

Atualmente, o único formato de arquivo para o qual é possível exportar a escultura de voxels feita é o formado .off, utilizado para a visualização de objetos 3D.

Para salvar seu arquivo em .off basta clicar no ultimo botão da barra de ferramentas ou ir em File>Save as .off. Ambas as opções irão abrir um diálogo para salvar seu arquivo nas pastas do seu sistema.


## Agradecimentos

Agradecemos a orientação do professor [Agostinho Brito](https://agostinhobritojr.github.io/) no desenvolvimento deste projeto ao longo do semestre.
