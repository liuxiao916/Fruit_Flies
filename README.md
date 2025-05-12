1. 准备配备 Linux 或 Windows 系统并安装 DrosoMating 软件的电脑。将待分析的视频文件传输至该电脑。启动 DrosoMating 软件，点击 “Open Video” 导入录制的交配行为视频。将处理速度设置为 4（速度与准确性的最佳平衡）。指定待分析的培养板（腔室）数量。  
*Prepare computer equipped either Linux or Windows PC with DrosoMating installed. Transfer video files into the computer to be analyzed. Launch DrosoMating and click “Open Video” to import the recorded mating video. Set processing speed to 4 (optimal balance between speed and accuracy). Specify the number of plates (chambers) to analyze.*
<p align="center">
  <img width="429" alt="image" src="https://github.com/user-attachments/assets/cb46640b-ab2f-4600-a8aa-6b43986695c7" />
  <br />
  <em>Figure 1. Analysis speed and chamber selection</em>
</p>

2. 按顺时针顺序选择四根钢标记柱。根据视频方向调整选择顺序。对于每个培养板，将显示一张预览图像。  
*Select the four steel marker pillars in clockwise order . Adjust the selection sequence based on the video orientation. For each plate, a preview image will appear.* 
 <p align="center">
 <img width="412" alt="image" src="https://github.com/user-attachments/assets/f1351c6c-00a2-4b5e-ae12-fc947adac15f" />
</p>

3. 点击单只果蝇的三个不同身体区域（如头部、胸部、腿部）以增强跟踪准确性。  
*Click on three distinct body regions (e.g., head, thorax, legs) of a single fly to enhance tracking accuracy.*
 <p align="center">
<img width="417" alt="image" src="https://github.com/user-attachments/assets/f6ef3ee0-6d80-4e2d-b4a5-c06a7995f57b" />
</p>
 
4. 选择所有区域后，返回至 “DrosoMating” 主界面。调整 x（水平方向）和 y（垂直方向）的值，使网格与培养室的孔洞对齐。通过修改 s 值（敏感度阈值）对果蝇检测进行微调，直至所有果蝇都被正确识别。利用网格将单只果蝇分割开来。  
*After selecting all regions, return to the DrosoMating home interface. Adjust x (horizontal) and y (vertical) values to align grids with chamber holes. Fine-tune fly detection by modifying the s value (sensitivity threshold) until all flies are correctly identified. Use the grid to segment individual flies.*
 <p align="center">
<img width="332" alt="image" src="https://github.com/user-attachments/assets/a69cd960-c761-426d-bc62-095eb5d4d4ea" />
</p>

5. 在完成上述参数设置与优化步骤后，用户可点击操作界面中的 “开始运行” 按钮，当进度条显示为 100% 时，此时可通过“导出结果”获取分析结果文件。将原始数据导出为 CSV 或 Excel 文件。在电子表格软件中打开该文件以进行进一步处理。  
*After completing the above parameter setting and optimization steps, the user can click the "Start Run" button in the operation interface. When the progress bar shows 100%, the user can obtain the analysis result file by clicking "Export Results". Export raw data as a CSV or Excel file. Open it in spreadsheet software for further processing.*

**Results：**  
Metrics
* courtship_duration(min): Total chasing time
* mate_duration(min): Mating duration
* CI: Courtship time / (mating time-courtship time)
* court_start_time(min): Time to first chasing
* mate_start_time(min): Mating start time
* mate_end_time(min): Mating end time

**Example Table:**   
<img width="303" alt="image" src="https://github.com/user-attachments/assets/4ddd8e9d-34f6-48b4-9d25-d023a0a70441" />

