<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Laberinto Móvil</title>
    <style>
        body { text-align: center; font-family: Arial, sans-serif; }
        canvas { background: #eee; display: block; margin: auto; }
        .controls { display: flex; justify-content: center; gap: 10px; margin-top: 10px; }
        button { padding: 10px; font-size: 20px; }
    </style>
</head>
<body>
    <h1>Laberinto</h1>
    <canvas id="gameCanvas" width="400" height="400"></canvas>
    <div class="controls">
        <button onclick="move('up')">⬆️</button>
    </div>
    <div class="controls">
        <button onclick="move('left')">⬅️</button>
        <button onclick="move('down')">⬇️</button>
        <button onclick="move('right')">➡️</button>
    </div>
    <script>
        const canvas = document.getElementById("gameCanvas");
        const ctx = canvas.getContext("2d");
        const tileSize = 40;
        const maze = [
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [1, 0, 0, 0, 1, 0, 1, 0, 0, 1],
            [1, 1, 1, 0, 1, 0, 1, 1, 0, 1],
            [1, 0, 1, 0, 0, 0, 1, 0, 0, 1],
            [1, 0, 1, 1, 1, 1, 1, 0, 1, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 0, 1, 1, 1, 1, 0, 1, 0, 1],
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
        ];
        let player = { x: 1, y: 1 };
        let victories = localStorage.getItem("victories") || 0;

        function drawMaze() {
            for (let y = 0; y < maze.length; y++) {
                for (let x = 0; x < maze[y].length; x++) {
                    ctx.fillStyle = maze[y][x] === 1 ? "black" : "white";
                    ctx.fillRect(x * tileSize, y * tileSize, tileSize, tileSize);
                }
            }
            ctx.fillStyle = "red";
            ctx.fillRect(player.x * tileSize, player.y * tileSize, tileSize, tileSize);
        }

        function move(direction) {
            let newX = player.x;
            let newY = player.y;
            if (direction === "up") newY--;
            if (direction === "down") newY++;
            if (direction === "left") newX--;
            if (direction === "right") newX++;
            
            if (maze[newY][newX] === 0) {
                player.x = newX;
                player.y = newY;
                drawMaze();
                checkWin();
            } else {
                player.x = 1;
                player.y = 1;
                alert("¡Has chocado! Vuelves al inicio.");
                drawMaze();
            }
        }
        
        function checkWin() {
            if (player.x === 8 && player.y === 8) {
                victories++;
                localStorage.setItem("victories", victories);
                alert("Has superado la prueba, te invitamos a nuestro escape room.");
                if (victories === 1) downloadVideo("reward1.mp4");
                if (victories === 5) downloadVideo("reward5.mp4");
                if (victories === 10) downloadVideo("reward10.mp4");
                if (victories === 20) downloadVideo("reward20.mp4");
                player.x = 1;
                player.y = 1;
                drawMaze();
            }
        }
        
        function downloadVideo(videoName) {
            let link = document.createElement("a");
            link.href = videoName;
            link.download = videoName;
            document.body.appendChild(link);
            link.click();
            document.body.removeChild(link);
        }
        
        drawMaze();
    </script>
</body>
</html>
