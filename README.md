# 42_cub3d

![screenshot](https://user-images.githubusercontent.com/62171131/109470351-a3742f80-7ab2-11eb-8f3d-5560491bb48c.jpg)

## 학습목표
레이캐스팅을 활용하여 1인칭 시점의 이동가능한 3D 그래픽을 표현한다.

## 주제
레이캐스팅(raycasting), 그래픽디자인, 알고리즘, 비트맵 파일

## 결과
100/100 통과(2021.02.20)

## 사용방법(macOS)
1. 레파지토리에서 make 합니다.
```
make
```

2. 시작화면의 스크린샷을 저장할 수 있습니다.
```
./cub3d --save map.cub
```

3. 게임을 실행할 수 있습니다.
```
./cub3d map.cub
```

4. 방향키와 WASD키를 사용하여 이동 또는 회전할 수 있습니다.

## 참고자료

[RGB색값](https://stdbc.tistory.com/62)
[수직거리계산](https://github.com/sungyongcho/ii2r/blob/master/md/6.md)
[레이캐스팅](https://github.com/365kim/raycasting_tutorial)
[카메라행렬](https://stdbc.tistory.com/67)
[비트맵파일](https://dojang.io/mod/page/view.php?id=702)
[비트맵헤더](https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries)
