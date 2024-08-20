# Fruit_Flies

1. 图像预处理与果蝇的分割

首先通过鼠标点击确定板子的固定桩所在位置，通过透视变换将视角进行标准化处理，从而按照图1的方式利用网格对每一对果蝇进行分割

![1](https://xiao-pic.oss-cn-shenzhen.aliyuncs.com/pic/img/20220710153919.png)

图1.果蝇分割

考虑到录制设备的稳定性因素，对板子固定桩的位置也进行了跟踪操作，以首次鼠标点击的位置为中心，选取矩形图像作为匹配模板，并在以上一次匹配所在位置为中心，设计ROI区域，在此区域内根据置信度选择最合适的位置作为本次匹配结果。

![2](https://xiao-pic.oss-cn-shenzhen.aliyuncs.com/pic/img/20220710154058.png)

图2.固定桩跟踪器（蓝色点为鼠标点击中心，红色矩形为匹配模板，绿色矩形为ROI区域）

通过上述方法可以将每一对果蝇稳定分割开并且稳定地确定其位置，具有较好的鲁棒性。

1. 果蝇的提取与追踪

首先对第一步中得到的板内区域进行灰度处理以及中值滤波，进而进行二值化处理

![3](https://xiao-pic.oss-cn-shenzhen.aliyuncs.com/pic/img/20220710154135.png)
图3.二值化图像

对二值化过后的图像进行轮廓提取，根据大小位置筛选出果蝇的轮廓，将轮廓中心作为果蝇的位置。

![4](https://xiao-pic.oss-cn-shenzhen.aliyuncs.com/pic/img/20220710154256.png)

图4.果蝇提取

果蝇追踪通过轨迹匹配算法实现，为两只果蝇分别创建轨迹，根据果蝇当前位置选择距离最近的一条轨迹作为更新后的位置。

1. 果蝇行为状态机原理

果蝇行为的状态切换通过状态机实现，果蝇状态列表如下：

1. 随机运动状态：果蝇行为没有明显规律，或是两只果蝇均不移动。
2. 求偶状态：表示雄果蝇正在对雌果蝇求偶。
3. 交配缓冲阶段：表示雄果蝇在尝试与雌果蝇交配，尚未交配成功。
4. 正式交配阶段：表示雄果蝇与雌果蝇交配成功。
5. 完成交配阶段：交配完成，雌雄果蝇分离。

通过判断雌雄果蝇的运动状态与位置判定果蝇当前的行为，实现状态的切换以及计时。


**Processing of Image and segmentation of fruit flies**

First, click the mouse to determine the location of the fixed pillar of the experiment board, so that we can get a standard view of the board through perspective transformation. Then we can segment each fruit flies as figure 1 by using a grid.

![1](https://xiao-pic.oss-cn-shenzhen.aliyuncs.com/pic/img/20220710153919.png)

Fig 1. Segmentation of fruit flies

To consider the stability of the recording equipment, we try to track the position of the fixed pillar of the experiment board. We take the position of the first mouse click as the center and select the rectangular image as the matching template. Next, we take the center of the last matching result to design the ROI (region of interest). Finally, the most suitable position is selected according to the confidence level in this area as the matching result.

![2](https://xiao-pic.oss-cn-shenzhen.aliyuncs.com/pic/img/20220710154058.png)

Fig 2. Fixed pillar tracker (the blue point is the center of the mouse click, the red rectangle is the matching template, and the green rectangle is the ROI area)

Through the above method, each pair of fruit flies can be separated stably. This method has good robustness so that we can determine the position of fruit flies stably.

**Extraction and tracking of fruit flies**

First, perform grayscale processing and median filtering on the experiment picture obtained from the processing step, and then set a threshold to perform binarization processing.

![3](https://xiao-pic.oss-cn-shenzhen.aliyuncs.com/pic/img/20220710154135.png)
Fig. 3 Binarized image

Next, we extract the outline of the binarized image. According to the size and position, we can select the outline of fruit flies. The center of the outline is taken as the position of the fruit fly.

![4](https://xiao-pic.oss-cn-shenzhen.aliyuncs.com/pic/img/20220710154256.png)

Fig4. Fruit flies extraction

The state machine of fruit flies’ behavior.

The state switching of fruit flies’ behavior is realized through a state machine. The list of fruit fly states is as follows:

1. Random movement state: There is no obvious regularity in the behavior of fruit flies, or neither fruit flies move.

2. Courtship status: the male fruit fly is courting the female fruit fly.

3. Mating buffer stage: It means that the male fruit flies are trying to mate with the female fruit flies, and they have not yet mate successfully.

4. Formal mating stage: indicates that the male fruit fly and the female fruit fly mate successfully.

5. Completing the mating stage: mating is completed, and the male and female flies are separated.
