# Gnuplot
붓꽃을 데이터에 따라 분류 및 Gnuplot을 활용해 이를 시각화 정리.

준비물 : Gnuplot, Visual Code(이외의 다른 IDE에서도 가능)


Part A

우리가 어떠한 데이터 A를 받았을 때 우리는 나중에 들어올 데이터 B가 이 데이터 A에 적합한 데이터인지 아닌지를 구별하기 위해서 데이터 A의 특징을 학습시킬려고 한다.
이 때 전체 데이터A를 training set으로 두게 된다면 training model밖에 만들 수가 없어서 test를 할 수가 없게 되기 때문에 알맞은 방법은 아니다. 고로, 데이터 A의 일부분을 test set으로 바꾼 뒤 나머지 부분만을 training model로 만든다.
하지만, 이런 식으로 진행을 하게 될 경우에 test set이 잘 맞으면 학습 모델이 잘 나왔다고 측정이 될 것이고 반대로 test set과 잘 맞지 않으면 학습 모델이 잘 나오지 않았다고 측정이 될 것이다.
우리가 원하는 목표는 나중에 들어올 데이터 B가 적합한 데이터인지 아닌지를 구별하는 것이지 test set이 잘 맞냐 안 맞냐 가 아니기 때문에 여러 번에 이어서 교차검증(k fold cross validation)을 해야 한다.
전체 데이터를 training set test set 이렇게 2부위로 나눈다. 물론 training set은 학습을 위한 모델을 만들어야 하므로 가장 큰 범위를 차지한다. 이 test set은 k번에 걸쳐서 학습 모델을 평가해 어떠한 학습 모델이 결과가 좋은지를 평가해 줄 것이다.
이렇게 나뉜 test set을 3번을 하게 될 시에 3 fold cross test를 5번을 하게 될 시엔 5 fold cross validation이라고 부른다.

![image](https://user-images.githubusercontent.com/96565110/147797294-0371ded0-313d-4f80-8cd3-8135ee79a69c.png)

PartB
1. 
밑의 그래프는 첫번째 특징인 sepal length(꽃받침의 길이)에 관한 그래프다. 
세 종류의 꽃들이 각기 순서대로 평균 길이가 길어진다는 것을 알 수가 있다.

![image](https://user-images.githubusercontent.com/96565110/147797304-f55f7b1b-d44c-4c75-8854-eacbaae98b29.png)

밑의 그래프는 두번째 특징인 sepal width(꽃받침 너비)에 관한 그래프다.
첫번째 꽃인 setosa의 경우엔 전체적으로 고루 분포가 되어 있고 versicolor의 경우엔 짧은 쪽으로 virginica는 3에서 평균치가 크게 높아지는 것을 확인 할 수가 있다.

![image](https://user-images.githubusercontent.com/96565110/147797306-3d4a501d-c45d-4cb0-b356-7f379b32a647.png)

세 번째 특징인 petal length(꽃잎의 길이)에 관한 그래프다.
Setosa의 경우엔 압도적으로 짧은 측면이 보이고 versicolor와 virginica는 setosa에 비해선 고루 분포 되어 있지만 앞의 두 가지 그래프 만큼 고루 분포 되진 않는 것을 볼 수 가 있다.

![image](https://user-images.githubusercontent.com/96565110/147797309-e0d23c96-3be8-48b5-ad94-13e09d1caf2a.png)

네 번째 특징인 petal width(꽃잎의 너비)에 관한 그래프다.
처음에 보여줬던 두가지 꽃받침의 관한 그래프와 달리 꽃잎의 경우엔 꽃잎들이 확연하게 차이가 난다는 것을 볼 수가 있다. 만일 꽃의 분리에 관한 식이 나온다면 앞의 두가지 경우보다 뒤의 두가지 측면에 대해 가산을 두는 방식으로 계산을 하는게 더 정확도 측면에서 올라갈 수가 있을 것이다.

![image](https://user-images.githubusercontent.com/96565110/147797312-3f1710b1-efb7-4dd1-9ceb-27aec33d2ae4.png)




![image](https://user-images.githubusercontent.com/96565110/147797313-a8ef00c8-42f9-4ffa-80bc-0f2f576096e7.png)

총합 4가지의 특성을 1 vs 2 ,1 vs 3, 1 vs 4, 2 vs 3, 2 vs 4, 3 vs 4로 총 6가지 측면으로 비교를 한 그래프다. 
Setosa의 경우에 sepal length와 sepal width는 1대1까진 아니어도 정비례해면서 그래프가 뻗어져 나가는 것을 확인할 수가 있다.
또한, sepal length : petal width, sepal length: petal length, sepal width : petal length, sepal length : petal width 등의 그래프를 보면 한쪽에 치우쳐진 그래프의 형태가 보인다. 이는 PartB의 첫번쨰 그래프에서 평균값이 크게 치우쳐지는 경향의 그래프들의 흔적일 것이다.
두번째 꽃인 versicolor의 경우에는 setosa 보다 6가지 측면 모두에서 비례하면서 뻗어 나가는  점들을 볼 수가 있다. 이를 통해 이 꽃의 경우엔 꽃받침과 꽃잎 등의 크기가 일정하게 뻗어져 나가는 것을 추측할 수가 있을 것이다.
세번째 꽃인 virginica또한 versicolor와 같이 비례하는 점들을 볼 수가 있지만 두번쨰 꽃보다도 더욱더 1대 1 정비례에 가까운 측면을 볼 수가 있다. 이에 따라 봤을 시 virginica의 경우에는 꽃잎의 크기만큼 꽃받침 또한 크다는 것을 확인 할 수가 있다.
