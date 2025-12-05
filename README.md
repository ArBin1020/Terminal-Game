# Terminal Game
這是一個基於Linux Terminal的C小遊戲

當我無聊的時候我就會上來更新這個專案，目前只支援 sudoku，預計未來會增加更多功能及遊戲

因目前依賴`<termios.h>``<sys/ioctl.h>`，所以只能在 Linux 上運行

# Quick Start
### setup
```bash
git clone https://github.com/ArBin1020/Terminal-Game.git
cd Terminal-Game

make
./game
```

### control

|key|action|
|--|--|
|⬆️ ⬇️ ⬅️ ➡️|move cursor|
|1-9|Input Number|
|0/Backspace/Del|Clear Cell|
|q|Quit Game|

