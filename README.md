# Geomeotry_Dash
 Tên: Trần Đức Quang
Mã SV: 24021610

Game: Geomeotry Dash Meltdown Remake. 
Đây là một game dựa trên game geometry dash meltdown của ROBTOB.
Cách chơi game đơn giản: ấn nút space để nhảy qua các chướng ngại vật được định sẵn, sau một khoảng thời gian nếu đi được đến cuối map sẽ thắng game.

*Các tính năng và thuật toán được sử dụng:
- Thư viện SDL2
-Các struct/class khác nhau được sử dụng để quản lí các đối tượng game khác nhau
- 4 dạng nhân vật được chuyển đổi tùy theo giai đoạn của game
- 4 loại màn hình chủ yếu ở trong game: menu chính, màn hình dừng, màn hình game và màn hình sau khi kết thúc game
- Xây dựng game map và va chạm map dựa theo hệ tọa độ oxy để vẽ từng ô ảnh hợp lí để tạo nên map
- Xử lí fps

*Chi tiết về từng hàm trong chương trình:
- Game_Character: Hàm chính xử lí tất cả mọi thứ liên quan đến nhân vật chính của game
- Game_object: Hàm xử lí mọi thứ có dạng hình chữ nhật với một texture và một sdl_rect
-Timer: Xử lí fps
-Gamemap: Hàm xây dựng bản đồ game
-Menu: Hàm xử lí các trạng thái khác nhau của game(game state menu, playing, finish và paused)
-Font: Hàm xử lí các vấn đề liên quan đến chữ và số liệu ngoài(highscore và số lần chơi)


*Các nguồn tham khảo cho từng phần của game:
- Hàm xây dựng map và va chạm map:https://www.youtube.com/results?search_query=phat+trien+phan+mem+123a+z
-Hàm nhân vật di chuyển, màn hình di chuyển, âm thanh, hình ảnh, font chữ,..: https://docs.google.com/document/d/1FZ3jTqHxtyZznNWiJmmve0zYu_aSliUqLP2OsMcdehQ/edit?tab=t.0#heading=h.g69r5ua9lzeh và trên cả lazyfoo: https://lazyfoo.net/tutorials/SDL/index.php

*Link Github cũ: https://github.com/24021610/24021610_TranDucQuang
-đây là link github lúc bắt đầu học sdl2 trước khi xây dựng các hàm chính của game



Checklisk khi chấm bài
(danh sách dưới đây liệt kê tính năng để giáo viên dễ chấm bài chứ không có nghĩa các bạn cần làm hết mới được 10 nhé)

Tự làm những phần nào, phần nào lấy từ các kiểu tutorial/code mẫu: Tự làm gần hết, trừ phần xử lí va chạm map(đã mở rộng) và phần xây map

Liệt kê các nguồn tham khảo (code, hình ảnh, âm thanh...) (đã liệt kê ở trên)

Dùng các lệnh vẽ hình: có (SDL_RenderCopyEx)

Texture: có

Background: có

Event bàn phím: có (xử lí trong nhân vật game)

Event chuột:có 

Animation (hoạt hình) có

Xử lý va chạm: có

Score (có tính điểm): có (lưu trong file highscore)

Lưu bảng điểm: có 

Sound: có (trong main)

Sound on off: có

Background music: có

Font: có (trong hàm font)

Menu: có (trong hàm menu)

Pause/Resume:có 

Status bar / lives (mạng/máu...): không

Các điểm nổi bật khác: các trạng thái khác nhau của nhân vật, xây dựng map, 

Code viết dễ đọc (gv đánh giá)

Hiểu rõ code (gv đánh giá)



