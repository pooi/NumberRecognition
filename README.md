<h1 align=center>Number Recognition</h1>

<br>
<br>

## Overview

미리 정해진 숫자를 인식하는 코드입니다.

숫자는 굴림, 견고딕, 한컴백제M 폰트 3가지 종류로 이루어져있고, 정형화된 크기와 위치에 숫자가 위치합니다.

이 프로그램은 위 3가지 폰트 및 정형화된 이미지에만 적용이 가능하므로 포함된 이미지가 아닌 다른 숫자가 적힌 이미지를 인식하려고 할 때에는 정확한 인식이 불가능할 수 있습니다.

A code that recognizes a predetermined number.

The numbers are composed of three types of <i>Gullim, Gyeongodic, and Hankeom Baegje M</i> fonts, and numbers are placed in standardized sizes and locations.

This program is only applicable to the above three fonts and standardized images, so it may not be possible to recognize correctly when trying to recognize images with numbers other than the included images.

<br><br>
## Feature
> 숫자를 검출하기 위해 다음 8가지의 특징을 활용합니다.<br>
> The following eight features are used to detect numbers.

<ul>
  <li> 좌우대칭(Vertical Symmetry)
  <li> 상하대칭(Horizontal Symmetry)
  <li> 수평선이 상단에 위치하는지(Is the horizontal line at the top?)
  <li> 수평선이 하단에 위치하는지(Is the horizontal line at the bottom?)
  <li> 수평선이 존재하지 않는지(Horizontal line does not exist)
  <li> 막혀있는 곳이 있는지(Is there a place that is closed?)
  <li> 막혀있는 곳이 있다면 상단인지 하단인지(If there a place that is closed, that position is top or bottom?)
  <li> 중심선이 걸치는 부분이 몇 개인지(How many overlap with the center line?)
</ul>

<br><br>

## How to Detect
Please refer to <a href="https://github.com/pooi/NumberRecognition/blob/master/Description.pdf">this</a> file.

<br><br>
## Usage
> 이 프로그램을 사용하기 위해서는 opencv가 필요합니다.<br>
> You need opencv to use this program.<br>
> <a href="http://www.opencv.org/releases.html">http://www.opencv.org/releases.html</a><br>
> 참고 : <a href="http://webnautes.tistory.com/716">http://webnautes.tistory.com/716</a>
```C
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

int main(){
  ...
  IplImage * src = cvLoadImage(fileName);
  ...
}
```

<br><br>
## Image
> 숫자 인식에 활용되는 이미지는 아래와 같습니다.<br>
> The image used for digit recognition is shown below.


<ul>
  <li> 굴림(<i>Gullim</i>)</li>
</ul>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B5%B4%EB%A6%BC/0.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B5%B4%EB%A6%BC/1.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B5%B4%EB%A6%BC/2.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B5%B4%EB%A6%BC/3.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B5%B4%EB%A6%BC/4.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B5%B4%EB%A6%BC/5.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B5%B4%EB%A6%BC/6.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B5%B4%EB%A6%BC/7.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B5%B4%EB%A6%BC/8.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B5%B4%EB%A6%BC/9.png" width=10%>

<ul>
  <li> 견고딕(<i>Gyeongodic</i>)</li>
</ul>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B2%AC%EA%B3%A0%EB%94%95/0.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B2%AC%EA%B3%A0%EB%94%95/1.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B2%AC%EA%B3%A0%EB%94%95/2.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B2%AC%EA%B3%A0%EB%94%95/3.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B2%AC%EA%B3%A0%EB%94%95/4.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B2%AC%EA%B3%A0%EB%94%95/5.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B2%AC%EA%B3%A0%EB%94%95/6.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B2%AC%EA%B3%A0%EB%94%95/7.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B2%AC%EA%B3%A0%EB%94%95/8.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%EA%B2%AC%EA%B3%A0%EB%94%95/9.png" width=10%>

<ul>
  <li> 한컴백제M(<i>Hankeom Baegje M</i>)</li>
</ul>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%ED%95%9C%EC%BB%B4%EB%B0%B1%EC%A0%9C/0.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%ED%95%9C%EC%BB%B4%EB%B0%B1%EC%A0%9C/1.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%ED%95%9C%EC%BB%B4%EB%B0%B1%EC%A0%9C/2.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%ED%95%9C%EC%BB%B4%EB%B0%B1%EC%A0%9C/3.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%ED%95%9C%EC%BB%B4%EB%B0%B1%EC%A0%9C/4.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%ED%95%9C%EC%BB%B4%EB%B0%B1%EC%A0%9C/5.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%ED%95%9C%EC%BB%B4%EB%B0%B1%EC%A0%9C/6.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%ED%95%9C%EC%BB%B4%EB%B0%B1%EC%A0%9C/7.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%ED%95%9C%EC%BB%B4%EB%B0%B1%EC%A0%9C/8.png" width=10%>
<img src="https://github.com/pooi/NumberRecognition/blob/master/NumberRecognition/NumberRecognition/%ED%95%9C%EC%BB%B4%EB%B0%B1%EC%A0%9C/9.png" width=10%>

<br><br>
## Result
```
# 굴림(Gullim)
==================================
input : 굴림\\0.png
예상 숫자 : 0
==================================
input : 굴림\\1.png
예상 숫자 : 1
==================================
input : 굴림\\2.png
예상 숫자 : 2
==================================
input : 굴림\\3.png
예상 숫자 : 3
==================================
input : 굴림\\4.png
예상 숫자 : 4
==================================
input : 굴림\\5.png
예상 숫자 : 5
==================================
input : 굴림\\6.png
예상 숫자 : 6
==================================
input : 굴림\\7.png
예상 숫자 : 7
==================================
input : 굴림\\8.png
예상 숫자 : 8
==================================
input : 굴림\\9.png
예상 숫자 : 9

# 견고딕(Gyeongodic)
==================================
input : 견고딕\\0.png
예상 숫자 : 0
==================================
input : 견고딕\\1.png
예상 숫자 : 1
==================================
input : 견고딕\\2.png
예상 숫자 : 2
==================================
input : 견고딕\\3.png
예상 숫자 : 3
==================================
input : 견고딕\\4.png
예상 숫자 : 4
==================================
input : 견고딕\\5.png
예상 숫자 : 5
==================================
input : 견고딕\\6.png
예상 숫자 : 6
==================================
input : 견고딕\\7.png
예상 숫자 : 7
==================================
input : 견고딕\\8.png
예상 숫자 : 8
==================================
input : 견고딕\\9.png
예상 숫자 : 9

# 한컴백제M(Hankeom Baegje M)
==================================
input : 한컴백제\\0.png
예상 숫자 : 0
==================================
input : 한컴백제\\1.png
예상 숫자 : 1
==================================
input : 한컴백제\\2.png
예상 숫자 : 2
==================================
input : 한컴백제\\3.png
예상 숫자 : 3
==================================
input : 한컴백제\\4.png
예상 숫자 : 4
==================================
input : 한컴백제\\5.png
예상 숫자 : 5
==================================
input : 한컴백제\\6.png
예상 숫자 : 6
==================================
input : 한컴백제\\7.png
예상 숫자 : 7
==================================
input : 한컴백제\\8.png
예상 숫자 : 8
==================================
input : 한컴백제\\9.png
예상 숫자 : 9
```
<br><br>
## License
```
    Copyright 2017 Taewoo You

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
```
