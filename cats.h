// ---- Cat 0: Sitting cat (front-facing, tail curled) ----
void drawCat0()
{
  int cx = 600, cy = 200;

  // Body
  epaper.fillCircle(cx, cy + 60, 70, TFT_BLACK);
  epaper.fillCircle(cx, cy + 60, 64, TFT_WHITE);

  // Head
  epaper.fillCircle(cx, cy - 40, 55, TFT_BLACK);
  epaper.fillCircle(cx, cy - 40, 49, TFT_WHITE);

  // Ears
  epaper.fillTriangle(cx - 45, cy - 75, cx - 25, cy - 110, cx - 10, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx - 40, cy - 78, cx - 27, cy - 102, cx - 15, cy - 70, TFT_WHITE);
  epaper.fillTriangle(cx + 45, cy - 75, cx + 25, cy - 110, cx + 10, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx + 40, cy - 78, cx + 27, cy - 102, cx + 15, cy - 70, TFT_WHITE);

  // Eyes
  epaper.fillCircle(cx - 20, cy - 45, 10, TFT_BLACK);
  epaper.fillCircle(cx + 20, cy - 45, 10, TFT_BLACK);
  epaper.fillCircle(cx - 18, cy - 47, 4, TFT_WHITE);
  epaper.fillCircle(cx + 22, cy - 47, 4, TFT_WHITE);

  // Nose
  epaper.fillTriangle(cx - 4, cy - 28, cx + 4, cy - 28, cx, cy - 23, TFT_BLACK);

  // Mouth
  epaper.drawLine(cx, cy - 23, cx - 8, cy - 17, TFT_BLACK);
  epaper.drawLine(cx, cy - 23, cx + 8, cy - 17, TFT_BLACK);

  // Whiskers
  epaper.drawLine(cx - 20, cy - 30, cx - 65, cy - 40, TFT_BLACK);
  epaper.drawLine(cx - 20, cy - 25, cx - 65, cy - 25, TFT_BLACK);
  epaper.drawLine(cx - 20, cy - 20, cx - 65, cy - 10, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 30, cx + 65, cy - 40, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 25, cx + 65, cy - 25, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 20, cx + 65, cy - 10, TFT_BLACK);

  // Front paws
  epaper.fillCircle(cx - 25, cy + 120, 18, TFT_BLACK);
  epaper.fillCircle(cx - 25, cy + 120, 13, TFT_WHITE);
  epaper.fillCircle(cx + 25, cy + 120, 18, TFT_BLACK);
  epaper.fillCircle(cx + 25, cy + 120, 13, TFT_WHITE);

  // Tail (curled to the right)
  for (int i = 0; i < 4; i++)
  {
    epaper.drawCircle(cx + 80, cy + 80, 40 + i, TFT_BLACK);
  }
  epaper.fillCircle(cx + 80, cy + 80, 37, TFT_WHITE);
  epaper.fillRect(cx - 10, cy + 40, 90, 85, TFT_WHITE);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Hello, I'm sitting here!", cx, 420, 4);
}

// ---- Cat 1: Sleeping cat (curled up, zzz) ----
void drawCat1()
{
  int cx = 600, cy = 220;

  // Curled body
  epaper.fillCircle(cx, cy, 90, TFT_BLACK);
  epaper.fillCircle(cx, cy, 83, TFT_WHITE);

  // Head resting on body
  epaper.fillCircle(cx - 55, cy - 40, 45, TFT_BLACK);
  epaper.fillCircle(cx - 55, cy - 40, 39, TFT_WHITE);

  // Ears
  epaper.fillTriangle(cx - 85, cy - 70, cx - 75, cy - 105, cx - 58, cy - 70, TFT_BLACK);
  epaper.fillTriangle(cx - 82, cy - 73, cx - 75, cy - 97, cx - 62, cy - 73, TFT_WHITE);
  epaper.fillTriangle(cx - 35, cy - 70, cx - 25, cy - 105, cx - 15, cy - 70, TFT_BLACK);
  epaper.fillTriangle(cx - 33, cy - 73, cx - 25, cy - 97, cx - 18, cy - 73, TFT_WHITE);

  // Closed eyes
  epaper.drawLine(cx - 72, cy - 42, cx - 60, cy - 48, TFT_BLACK);
  epaper.drawLine(cx - 60, cy - 48, cx - 48, cy - 42, TFT_BLACK);
  epaper.drawLine(cx - 42, cy - 42, cx - 30, cy - 48, TFT_BLACK);
  epaper.drawLine(cx - 30, cy - 48, cx - 18, cy - 42, TFT_BLACK);

  // Nose
  epaper.fillTriangle(cx - 58, cy - 30, cx - 52, cy - 30, cx - 55, cy - 26, TFT_BLACK);

  // Tiny smile
  epaper.drawLine(cx - 55, cy - 26, cx - 60, cy - 22, TFT_BLACK);
  epaper.drawLine(cx - 55, cy - 26, cx - 50, cy - 22, TFT_BLACK);

  // Tail curling around
  for (int i = 0; i < 5; i++)
  {
    epaper.drawCircle(cx + 40, cy - 20, 50 + i, TFT_BLACK);
  }
  epaper.fillCircle(cx + 40, cy - 20, 47, TFT_WHITE);
  epaper.fillRect(cx - 10, cy - 75, 100, 60, TFT_WHITE);
  epaper.fillRect(cx + 40, cy - 20, 60, 60, TFT_WHITE);

  // Zzz
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("z", cx + 20, cy - 115, 2);
  epaper.drawCentreString("Z", cx + 45, cy - 135, 4);
  epaper.drawCentreString("Z", cx + 75, cy - 165, 4);

  // Whiskers
  epaper.drawLine(cx - 70, cy - 30, cx - 105, cy - 40, TFT_BLACK);
  epaper.drawLine(cx - 70, cy - 27, cx - 105, cy - 27, TFT_BLACK);
  epaper.drawLine(cx - 40, cy - 30, cx - 5, cy - 40, TFT_BLACK);
  epaper.drawLine(cx - 40, cy - 27, cx - 5, cy - 27, TFT_BLACK);

  // Caption
  epaper.drawCentreString("Shhh... nap time", cx, 420, 4);
}

// ---- Cat 2: Playful cat (paw raised, wide eyes) ----
void drawCat2()
{
  int cx = 600, cy = 200;

  // Body
  epaper.fillCircle(cx, cy + 60, 70, TFT_BLACK);
  epaper.fillCircle(cx, cy + 60, 64, TFT_WHITE);

  // Head
  epaper.fillCircle(cx, cy - 40, 55, TFT_BLACK);
  epaper.fillCircle(cx, cy - 40, 49, TFT_WHITE);

  // Ears
  epaper.fillTriangle(cx - 45, cy - 75, cx - 25, cy - 110, cx - 10, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx - 40, cy - 78, cx - 27, cy - 102, cx - 15, cy - 70, TFT_WHITE);
  epaper.fillTriangle(cx + 45, cy - 75, cx + 25, cy - 110, cx + 10, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx + 40, cy - 78, cx + 27, cy - 102, cx + 15, cy - 70, TFT_WHITE);

  // Big wide eyes
  epaper.fillCircle(cx - 22, cy - 48, 14, TFT_BLACK);
  epaper.fillCircle(cx + 22, cy - 48, 14, TFT_BLACK);
  epaper.fillCircle(cx - 18, cy - 52, 6, TFT_WHITE);
  epaper.fillCircle(cx + 26, cy - 52, 6, TFT_WHITE);
  epaper.fillCircle(cx - 24, cy - 44, 3, TFT_WHITE);
  epaper.fillCircle(cx + 20, cy - 44, 3, TFT_WHITE);

  // Nose
  epaper.fillTriangle(cx - 4, cy - 28, cx + 4, cy - 28, cx, cy - 23, TFT_BLACK);

  // Open mouth
  epaper.drawLine(cx, cy - 23, cx - 10, cy - 15, TFT_BLACK);
  epaper.drawLine(cx, cy - 23, cx + 10, cy - 15, TFT_BLACK);
  epaper.drawLine(cx - 10, cy - 15, cx + 10, cy - 15, TFT_BLACK);

  // Whiskers
  epaper.drawLine(cx - 20, cy - 30, cx - 65, cy - 40, TFT_BLACK);
  epaper.drawLine(cx - 20, cy - 25, cx - 65, cy - 25, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 30, cx + 65, cy - 40, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 25, cx + 65, cy - 25, TFT_BLACK);

  // Right paw raised
  epaper.drawLine(cx + 50, cy + 30, cx + 90, cy - 20, TFT_BLACK);
  epaper.drawLine(cx + 52, cy + 30, cx + 92, cy - 20, TFT_BLACK);
  epaper.fillCircle(cx + 91, cy - 25, 15, TFT_BLACK);
  epaper.fillCircle(cx + 91, cy - 25, 10, TFT_WHITE);
  epaper.fillCircle(cx + 85, cy - 35, 4, TFT_BLACK);
  epaper.fillCircle(cx + 95, cy - 35, 4, TFT_BLACK);
  epaper.fillCircle(cx + 100, cy - 26, 4, TFT_BLACK);

  // Left paw
  epaper.fillCircle(cx - 25, cy + 120, 18, TFT_BLACK);
  epaper.fillCircle(cx - 25, cy + 120, 13, TFT_WHITE);

  // Tail (upright)
  epaper.drawLine(cx + 60, cy + 100, cx + 85, cy - 10, TFT_BLACK);
  epaper.drawLine(cx + 61, cy + 100, cx + 86, cy - 10, TFT_BLACK);
  epaper.drawLine(cx + 62, cy + 100, cx + 87, cy - 10, TFT_BLACK);
  epaper.drawLine(cx + 86, cy - 10, cx + 75, cy - 25, TFT_BLACK);
  epaper.drawLine(cx + 87, cy - 10, cx + 76, cy - 25, TFT_BLACK);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Play with me!", cx, 420, 4);
}

// ---- Cat 3: Grumpy cat (furrowed brows, frown) ----
void drawCat3()
{
  int cx = 600, cy = 200;

  // Body
  epaper.fillCircle(cx, cy + 60, 70, TFT_BLACK);
  epaper.fillCircle(cx, cy + 60, 64, TFT_WHITE);

  // Head
  epaper.fillCircle(cx, cy - 40, 55, TFT_BLACK);
  epaper.fillCircle(cx, cy - 40, 49, TFT_WHITE);

  // Ears (slightly flattened)
  epaper.fillTriangle(cx - 50, cy - 70, cx - 30, cy - 108, cx - 8, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx - 45, cy - 73, cx - 30, cy - 100, cx - 13, cy - 70, TFT_WHITE);
  epaper.fillTriangle(cx + 50, cy - 70, cx + 30, cy - 108, cx + 8, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx + 45, cy - 73, cx + 30, cy - 100, cx + 13, cy - 70, TFT_WHITE);

  // Angry eyes
  epaper.fillCircle(cx - 20, cy - 45, 10, TFT_BLACK);
  epaper.fillCircle(cx + 20, cy - 45, 10, TFT_BLACK);
  epaper.fillCircle(cx - 18, cy - 47, 4, TFT_WHITE);
  epaper.fillCircle(cx + 22, cy - 47, 4, TFT_WHITE);

  // Furrowed brows
  epaper.drawLine(cx - 32, cy - 62, cx - 12, cy - 56, TFT_BLACK);
  epaper.drawLine(cx - 32, cy - 61, cx - 12, cy - 55, TFT_BLACK);
  epaper.drawLine(cx + 32, cy - 62, cx + 12, cy - 56, TFT_BLACK);
  epaper.drawLine(cx + 32, cy - 61, cx + 12, cy - 55, TFT_BLACK);

  // Nose
  epaper.fillTriangle(cx - 4, cy - 28, cx + 4, cy - 28, cx, cy - 23, TFT_BLACK);

  // Frown
  epaper.drawLine(cx - 15, cy - 18, cx - 5, cy - 14, TFT_BLACK);
  epaper.drawLine(cx - 5, cy - 14, cx + 5, cy - 14, TFT_BLACK);
  epaper.drawLine(cx + 5, cy - 14, cx + 15, cy - 18, TFT_BLACK);

  // Whiskers (droopy)
  epaper.drawLine(cx - 20, cy - 28, cx - 65, cy - 20, TFT_BLACK);
  epaper.drawLine(cx - 20, cy - 25, cx - 65, cy - 18, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 28, cx + 65, cy - 20, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 25, cx + 65, cy - 18, TFT_BLACK);

  // Front paws
  epaper.fillCircle(cx - 25, cy + 120, 18, TFT_BLACK);
  epaper.fillCircle(cx - 25, cy + 120, 13, TFT_WHITE);
  epaper.fillCircle(cx + 25, cy + 120, 18, TFT_BLACK);
  epaper.fillCircle(cx + 25, cy + 120, 13, TFT_WHITE);

  // Tail (low, annoyed)
  epaper.drawLine(cx - 65, cy + 100, cx - 110, cy + 80, TFT_BLACK);
  epaper.drawLine(cx - 65, cy + 101, cx - 110, cy + 81, TFT_BLACK);
  epaper.drawLine(cx - 65, cy + 102, cx - 110, cy + 82, TFT_BLACK);
  epaper.drawLine(cx - 110, cy + 80, cx - 120, cy + 90, TFT_BLACK);
  epaper.drawLine(cx - 110, cy + 81, cx - 120, cy + 91, TFT_BLACK);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Not amused.", cx, 420, 4);
}

// ---- Cat 4: Cat with fish ----
void drawCat4()
{
  int cx = 540, cy = 200; // Shifted for right half, leaving room for fish

  // Body
  epaper.fillCircle(cx, cy + 60, 70, TFT_BLACK);
  epaper.fillCircle(cx, cy + 60, 64, TFT_WHITE);

  // Head
  epaper.fillCircle(cx, cy - 40, 55, TFT_BLACK);
  epaper.fillCircle(cx, cy - 40, 49, TFT_WHITE);

  // Ears
  epaper.fillTriangle(cx - 45, cy - 75, cx - 25, cy - 110, cx - 10, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx - 40, cy - 78, cx - 27, cy - 102, cx - 15, cy - 70, TFT_WHITE);
  epaper.fillTriangle(cx + 45, cy - 75, cx + 25, cy - 110, cx + 10, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx + 40, cy - 78, cx + 27, cy - 102, cx + 15, cy - 70, TFT_WHITE);

  // Happy eyes
  epaper.drawLine(cx - 30, cy - 42, cx - 20, cy - 52, TFT_BLACK);
  epaper.drawLine(cx - 20, cy - 52, cx - 10, cy - 42, TFT_BLACK);
  epaper.drawLine(cx - 29, cy - 41, cx - 20, cy - 50, TFT_BLACK);
  epaper.drawLine(cx - 20, cy - 50, cx - 11, cy - 41, TFT_BLACK);
  epaper.drawLine(cx + 10, cy - 42, cx + 20, cy - 52, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 52, cx + 30, cy - 42, TFT_BLACK);
  epaper.drawLine(cx + 11, cy - 41, cx + 20, cy - 50, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 50, cx + 29, cy - 41, TFT_BLACK);

  // Nose
  epaper.fillTriangle(cx - 4, cy - 28, cx + 4, cy - 28, cx, cy - 23, TFT_BLACK);

  // Big smile
  epaper.drawLine(cx, cy - 23, cx - 12, cy - 13, TFT_BLACK);
  epaper.drawLine(cx, cy - 23, cx + 12, cy - 13, TFT_BLACK);

  // Whiskers
  epaper.drawLine(cx - 20, cy - 30, cx - 65, cy - 38, TFT_BLACK);
  epaper.drawLine(cx - 20, cy - 25, cx - 65, cy - 25, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 30, cx + 65, cy - 38, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 25, cx + 65, cy - 25, TFT_BLACK);

  // Front paws
  epaper.fillCircle(cx - 25, cy + 120, 18, TFT_BLACK);
  epaper.fillCircle(cx - 25, cy + 120, 13, TFT_WHITE);
  epaper.fillCircle(cx + 25, cy + 120, 18, TFT_BLACK);
  epaper.fillCircle(cx + 25, cy + 120, 13, TFT_WHITE);

  // --- Fish (to the right of the cat) ---
  int fx = 690, fy = 160;

  // Fish body
  epaper.fillCircle(fx, fy, 30, TFT_BLACK);
  epaper.fillCircle(fx, fy, 25, TFT_WHITE);
  epaper.fillCircle(fx - 15, fy, 25, TFT_BLACK);
  epaper.fillCircle(fx - 15, fy, 20, TFT_WHITE);
  epaper.fillCircle(fx + 10, fy, 22, TFT_BLACK);
  epaper.fillCircle(fx + 10, fy, 17, TFT_WHITE);

  // Fish tail
  epaper.fillTriangle(fx + 30, fy, fx + 55, fy - 25, fx + 55, fy + 25, TFT_BLACK);
  epaper.fillTriangle(fx + 33, fy, fx + 52, fy - 20, fx + 52, fy + 20, TFT_WHITE);

  // Fish eye
  epaper.fillCircle(fx - 20, fy - 5, 5, TFT_BLACK);
  epaper.fillCircle(fx - 18, fy - 6, 2, TFT_WHITE);

  // Fish mouth
  epaper.drawLine(fx - 38, fy + 2, fx - 30, fy - 2, TFT_BLACK);
  epaper.drawLine(fx - 38, fy + 2, fx - 30, fy + 6, TFT_BLACK);

  // Fish fin (top)
  epaper.fillTriangle(fx - 5, fy - 17, fx + 5, fy - 40, fx + 15, fy - 17, TFT_BLACK);
  epaper.fillTriangle(fx - 2, fy - 19, fx + 5, fy - 35, fx + 12, fy - 19, TFT_WHITE);

  // Hearts between cat and fish
  int hx = 630, hy = 120;
  epaper.fillCircle(hx - 6, hy - 4, 6, TFT_BLACK);
  epaper.fillCircle(hx + 6, hy - 4, 6, TFT_BLACK);
  epaper.fillTriangle(hx - 12, hy - 2, hx + 12, hy - 2, hx, hy + 14, TFT_BLACK);

  int hx2 = 650, hy2 = 100;
  epaper.fillCircle(hx2 - 4, hy2 - 3, 4, TFT_BLACK);
  epaper.fillCircle(hx2 + 4, hy2 - 3, 4, TFT_BLACK);
  epaper.fillTriangle(hx2 - 8, hy2 - 1, hx2 + 8, hy2 - 1, hx2, hy2 + 10, TFT_BLACK);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Fish is life <3", 600, 420, 4);
}

// ---- Cat 5: Stretching cat (yoga pose, bum up) ----
void drawCat5()
{
  int cx = 600, cy = 230;

  // Back body (angled oval, bum raised)
  epaper.fillCircle(cx + 40, cy - 30, 50, TFT_BLACK);
  epaper.fillCircle(cx + 40, cy - 30, 44, TFT_WHITE);

  // Front body (lower, stretched forward)
  epaper.fillCircle(cx - 50, cy + 30, 45, TFT_BLACK);
  epaper.fillCircle(cx - 50, cy + 30, 39, TFT_WHITE);

  // Connect body (fill gap)
  epaper.fillTriangle(cx - 20, cy + 10, cx + 10, cy - 10, cx + 10, cy + 30, TFT_BLACK);
  epaper.fillTriangle(cx - 18, cy + 12, cx + 8, cy - 6, cx + 8, cy + 28, TFT_WHITE);

  // Head (low, on the ground, front paws stretched)
  epaper.fillCircle(cx - 100, cy + 50, 40, TFT_BLACK);
  epaper.fillCircle(cx - 100, cy + 50, 34, TFT_WHITE);

  // Ears
  epaper.fillTriangle(cx - 130, cy + 20, cx - 118, cy - 8, cx - 105, cy + 22, TFT_BLACK);
  epaper.fillTriangle(cx - 127, cy + 22, cx - 118, cy - 1, cx - 108, cy + 24, TFT_WHITE);
  epaper.fillTriangle(cx - 80, cy + 20, cx - 68, cy - 8, cx - 55, cy + 22, TFT_BLACK);
  epaper.fillTriangle(cx - 77, cy + 22, cx - 68, cy - 1, cx - 58, cy + 24, TFT_WHITE);

  // Eyes (relaxed, half-closed)
  epaper.drawLine(cx - 118, cy + 45, cx - 108, cy + 42, TFT_BLACK);
  epaper.drawLine(cx - 108, cy + 42, cx - 98, cy + 45, TFT_BLACK);
  epaper.drawLine(cx - 90, cy + 45, cx - 80, cy + 42, TFT_BLACK);
  epaper.drawLine(cx - 80, cy + 42, cx - 70, cy + 45, TFT_BLACK);

  // Nose
  epaper.fillTriangle(cx - 103, cy + 55, cx - 97, cy + 55, cx - 100, cy + 59, TFT_BLACK);

  // Front paws (stretched way forward)
  epaper.drawLine(cx - 85, cy + 75, cx - 140, cy + 95, TFT_BLACK);
  epaper.drawLine(cx - 85, cy + 76, cx - 140, cy + 96, TFT_BLACK);
  epaper.fillCircle(cx - 143, cy + 95, 10, TFT_BLACK);
  epaper.fillCircle(cx - 143, cy + 95, 6, TFT_WHITE);
  epaper.drawLine(cx - 70, cy + 75, cx - 130, cy + 100, TFT_BLACK);
  epaper.drawLine(cx - 70, cy + 76, cx - 130, cy + 101, TFT_BLACK);
  epaper.fillCircle(cx - 133, cy + 100, 10, TFT_BLACK);
  epaper.fillCircle(cx - 133, cy + 100, 6, TFT_WHITE);

  // Back legs (standing)
  epaper.drawLine(cx + 25, cy + 10, cx + 15, cy + 80, TFT_BLACK);
  epaper.drawLine(cx + 26, cy + 10, cx + 16, cy + 80, TFT_BLACK);
  epaper.fillCircle(cx + 15, cy + 83, 12, TFT_BLACK);
  epaper.fillCircle(cx + 15, cy + 83, 7, TFT_WHITE);
  epaper.drawLine(cx + 55, cy + 10, cx + 50, cy + 80, TFT_BLACK);
  epaper.drawLine(cx + 56, cy + 10, cx + 51, cy + 80, TFT_BLACK);
  epaper.fillCircle(cx + 50, cy + 83, 12, TFT_BLACK);
  epaper.fillCircle(cx + 50, cy + 83, 7, TFT_WHITE);

  // Tail (high and curly)
  for (int i = 0; i < 4; i++)
  {
    epaper.drawCircle(cx + 90, cy - 70, 30 + i, TFT_BLACK);
  }
  epaper.fillCircle(cx + 90, cy - 70, 27, TFT_WHITE);
  epaper.fillRect(cx + 30, cy - 70, 60, 45, TFT_WHITE);
  epaper.fillRect(cx + 90, cy - 70, 35, 35, TFT_WHITE);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Stretch time!", 600, 420, 4);
}

// ---- Cat 6: Cat in a box ----
void drawCat6()
{
  int cx = 600, cy = 230;

  // Box (open top)
  int bx = cx - 80, by = cy - 20, bw = 160, bh = 110;
  epaper.drawRect(bx, by, bw, bh, TFT_BLACK);
  epaper.drawRect(bx + 1, by + 1, bw - 2, bh - 2, TFT_BLACK);
  // Box flaps (folded outward)
  epaper.drawLine(bx, by, bx - 25, by - 20, TFT_BLACK);
  epaper.drawLine(bx + 1, by, bx - 24, by - 20, TFT_BLACK);
  epaper.drawLine(bx - 25, by - 20, bx + 30, by - 20, TFT_BLACK);
  epaper.drawLine(bx + 30, by - 20, bx + 30, by, TFT_BLACK);
  epaper.drawLine(bx + bw, by, bx + bw + 25, by - 20, TFT_BLACK);
  epaper.drawLine(bx + bw - 1, by, bx + bw + 24, by - 20, TFT_BLACK);
  epaper.drawLine(bx + bw + 25, by - 20, bx + bw - 30, by - 20, TFT_BLACK);
  epaper.drawLine(bx + bw - 30, by - 20, bx + bw - 30, by, TFT_BLACK);

  // Cat head poking out of box
  epaper.fillCircle(cx, cy - 55, 50, TFT_BLACK);
  epaper.fillCircle(cx, cy - 55, 44, TFT_WHITE);

  // Ears
  epaper.fillTriangle(cx - 42, cy - 88, cx - 24, cy - 120, cx - 8, cy - 80, TFT_BLACK);
  epaper.fillTriangle(cx - 38, cy - 90, cx - 25, cy - 114, cx - 12, cy - 83, TFT_WHITE);
  epaper.fillTriangle(cx + 42, cy - 88, cx + 24, cy - 120, cx + 8, cy - 80, TFT_BLACK);
  epaper.fillTriangle(cx + 38, cy - 90, cx + 25, cy - 114, cx + 12, cy - 83, TFT_WHITE);

  // Eyes (big and curious, peeking)
  epaper.fillCircle(cx - 18, cy - 60, 12, TFT_BLACK);
  epaper.fillCircle(cx + 18, cy - 60, 12, TFT_BLACK);
  epaper.fillCircle(cx - 15, cy - 63, 5, TFT_WHITE);
  epaper.fillCircle(cx + 21, cy - 63, 5, TFT_WHITE);
  epaper.fillCircle(cx - 20, cy - 56, 3, TFT_WHITE);
  epaper.fillCircle(cx + 16, cy - 56, 3, TFT_WHITE);

  // Nose
  epaper.fillTriangle(cx - 4, cy - 42, cx + 4, cy - 42, cx, cy - 37, TFT_BLACK);

  // Whiskers
  epaper.drawLine(cx - 18, cy - 40, cx - 60, cy - 48, TFT_BLACK);
  epaper.drawLine(cx - 18, cy - 36, cx - 60, cy - 36, TFT_BLACK);
  epaper.drawLine(cx + 18, cy - 40, cx + 60, cy - 48, TFT_BLACK);
  epaper.drawLine(cx + 18, cy - 36, cx + 60, cy - 36, TFT_BLACK);

  // Paws draped over box edge
  epaper.fillCircle(bx + 30, by + 4, 14, TFT_BLACK);
  epaper.fillCircle(bx + 30, by + 4, 9, TFT_WHITE);
  epaper.fillCircle(bx + bw - 30, by + 4, 14, TFT_BLACK);
  epaper.fillCircle(bx + bw - 30, by + 4, 9, TFT_WHITE);

  // Erase head overlap with box interior
  epaper.fillRect(bx + 2, by + 2, bw - 4, bh - 4, TFT_WHITE);
  // Redraw box front edge
  epaper.drawLine(bx, by, bx + bw, by, TFT_BLACK);
  epaper.drawLine(bx, by + 1, bx + bw, by + 1, TFT_BLACK);
  // Redraw paws on top of box edge
  epaper.fillCircle(bx + 30, by, 14, TFT_BLACK);
  epaper.fillCircle(bx + 30, by, 9, TFT_WHITE);
  epaper.fillCircle(bx + bw - 30, by, 14, TFT_BLACK);
  epaper.fillCircle(bx + bw - 30, by, 9, TFT_WHITE);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("If it fits, I sits", 600, 420, 4);
}

// ---- Cat 7: Startled cat (arched back, puffed tail) ----
void drawCat7()
{
  int cx = 600, cy = 240;

  // Arched body (high arc using thick curve)
  for (int i = 0; i < 6; i++)
  {
    epaper.drawCircle(cx, cy + 60, 100 + i, TFT_BLACK);
  }
  // Erase inside and below to leave just the arch
  epaper.fillCircle(cx, cy + 60, 97, TFT_WHITE);
  epaper.fillRect(cx - 120, cy + 60, 240, 110, TFT_WHITE);

  // Head (turned slightly, wide-eyed)
  epaper.fillCircle(cx - 80, cy - 10, 42, TFT_BLACK);
  epaper.fillCircle(cx - 80, cy - 10, 36, TFT_WHITE);

  // Ears (pointed up, alert)
  epaper.fillTriangle(cx - 110, cy - 38, cx - 100, cy - 72, cx - 85, cy - 38, TFT_BLACK);
  epaper.fillTriangle(cx - 107, cy - 40, cx - 100, cy - 65, cx - 88, cy - 40, TFT_WHITE);
  epaper.fillTriangle(cx - 65, cy - 38, cx - 55, cy - 72, cx - 45, cy - 38, TFT_BLACK);
  epaper.fillTriangle(cx - 63, cy - 40, cx - 55, cy - 65, cx - 48, cy - 40, TFT_WHITE);

  // Wide shocked eyes
  epaper.fillCircle(cx - 95, cy - 14, 12, TFT_BLACK);
  epaper.fillCircle(cx - 68, cy - 14, 12, TFT_BLACK);
  epaper.fillCircle(cx - 95, cy - 14, 7, TFT_WHITE);
  epaper.fillCircle(cx - 68, cy - 14, 7, TFT_WHITE);
  // Tiny pupils
  epaper.fillCircle(cx - 93, cy - 14, 3, TFT_BLACK);
  epaper.fillCircle(cx - 66, cy - 14, 3, TFT_BLACK);

  // Open mouth (shocked O)
  epaper.drawCircle(cx - 80, cy + 8, 6, TFT_BLACK);
  epaper.drawCircle(cx - 80, cy + 8, 5, TFT_BLACK);

  // Whiskers (sticking out straight — startled)
  epaper.drawLine(cx - 95, cy, cx - 140, cy - 10, TFT_BLACK);
  epaper.drawLine(cx - 95, cy + 3, cx - 140, cy + 3, TFT_BLACK);
  epaper.drawLine(cx - 95, cy + 6, cx - 140, cy + 16, TFT_BLACK);
  epaper.drawLine(cx - 65, cy, cx - 20, cy - 10, TFT_BLACK);
  epaper.drawLine(cx - 65, cy + 3, cx - 20, cy + 3, TFT_BLACK);
  epaper.drawLine(cx - 65, cy + 6, cx - 20, cy + 16, TFT_BLACK);

  // Front legs
  epaper.drawLine(cx - 60, cy + 40, cx - 65, cy + 95, TFT_BLACK);
  epaper.drawLine(cx - 59, cy + 40, cx - 64, cy + 95, TFT_BLACK);
  epaper.fillCircle(cx - 65, cy + 98, 10, TFT_BLACK);
  epaper.fillCircle(cx - 65, cy + 98, 6, TFT_WHITE);
  epaper.drawLine(cx - 40, cy + 50, cx - 42, cy + 95, TFT_BLACK);
  epaper.drawLine(cx - 39, cy + 50, cx - 41, cy + 95, TFT_BLACK);
  epaper.fillCircle(cx - 42, cy + 98, 10, TFT_BLACK);
  epaper.fillCircle(cx - 42, cy + 98, 6, TFT_WHITE);

  // Back legs
  epaper.drawLine(cx + 50, cy + 40, cx + 55, cy + 95, TFT_BLACK);
  epaper.drawLine(cx + 51, cy + 40, cx + 56, cy + 95, TFT_BLACK);
  epaper.fillCircle(cx + 55, cy + 98, 10, TFT_BLACK);
  epaper.fillCircle(cx + 55, cy + 98, 6, TFT_WHITE);
  epaper.drawLine(cx + 70, cy + 30, cx + 75, cy + 95, TFT_BLACK);
  epaper.drawLine(cx + 71, cy + 30, cx + 76, cy + 95, TFT_BLACK);
  epaper.fillCircle(cx + 75, cy + 98, 10, TFT_BLACK);
  epaper.fillCircle(cx + 75, cy + 98, 6, TFT_WHITE);

  // Puffed-up tail (big and bushy, zigzag outline)
  epaper.fillCircle(cx + 95, cy - 10, 18, TFT_BLACK);
  epaper.fillCircle(cx + 105, cy - 30, 16, TFT_BLACK);
  epaper.fillCircle(cx + 95, cy - 50, 14, TFT_BLACK);
  epaper.fillCircle(cx + 110, cy - 65, 12, TFT_BLACK);
  // White cores to make it look fluffy
  epaper.fillCircle(cx + 95, cy - 10, 10, TFT_WHITE);
  epaper.fillCircle(cx + 105, cy - 30, 9, TFT_WHITE);
  epaper.fillCircle(cx + 95, cy - 50, 7, TFT_WHITE);
  epaper.fillCircle(cx + 110, cy - 65, 5, TFT_WHITE);

  // Exclamation marks
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("!", cx - 40, cy - 70, 4);
  epaper.drawCentreString("!", cx - 20, cy - 80, 4);

  // Caption
  epaper.drawCentreString("WHAT WAS THAT?!", 600, 420, 4);
}

// ---- Cat 8: Cat loaf (bread loaf position, tucked paws) ----
void drawCat8()
{
  int cx = 600, cy = 220;

  // Loaf body (wide rounded rectangle shape)
  epaper.fillCircle(cx - 60, cy + 20, 55, TFT_BLACK);
  epaper.fillCircle(cx + 60, cy + 20, 55, TFT_BLACK);
  epaper.fillRect(cx - 60, cy - 35, 120, 110, TFT_BLACK);
  epaper.fillCircle(cx - 60, cy + 20, 49, TFT_WHITE);
  epaper.fillCircle(cx + 60, cy + 20, 49, TFT_WHITE);
  epaper.fillRect(cx - 60, cy - 29, 120, 98, TFT_WHITE);

  // Head
  epaper.fillCircle(cx, cy - 60, 50, TFT_BLACK);
  epaper.fillCircle(cx, cy - 60, 44, TFT_WHITE);

  // Ears
  epaper.fillTriangle(cx - 42, cy - 92, cx - 25, cy - 128, cx - 8, cy - 85, TFT_BLACK);
  epaper.fillTriangle(cx - 38, cy - 94, cx - 26, cy - 121, cx - 12, cy - 88, TFT_WHITE);
  epaper.fillTriangle(cx + 42, cy - 92, cx + 25, cy - 128, cx + 8, cy - 85, TFT_BLACK);
  epaper.fillTriangle(cx + 38, cy - 94, cx + 26, cy - 121, cx + 12, cy - 88, TFT_WHITE);

  // Content half-closed eyes
  epaper.drawLine(cx - 28, cy - 62, cx - 18, cy - 68, TFT_BLACK);
  epaper.drawLine(cx - 18, cy - 68, cx - 8, cy - 62, TFT_BLACK);
  epaper.drawLine(cx - 27, cy - 61, cx - 18, cy - 66, TFT_BLACK);
  epaper.drawLine(cx - 18, cy - 66, cx - 9, cy - 61, TFT_BLACK);
  epaper.drawLine(cx + 8, cy - 62, cx + 18, cy - 68, TFT_BLACK);
  epaper.drawLine(cx + 18, cy - 68, cx + 28, cy - 62, TFT_BLACK);
  epaper.drawLine(cx + 9, cy - 61, cx + 18, cy - 66, TFT_BLACK);
  epaper.drawLine(cx + 18, cy - 66, cx + 27, cy - 61, TFT_BLACK);

  // Nose
  epaper.fillTriangle(cx - 4, cy - 48, cx + 4, cy - 48, cx, cy - 43, TFT_BLACK);

  // Tiny smile
  epaper.drawLine(cx, cy - 43, cx - 6, cy - 38, TFT_BLACK);
  epaper.drawLine(cx, cy - 43, cx + 6, cy - 38, TFT_BLACK);

  // Whiskers
  epaper.drawLine(cx - 18, cy - 48, cx - 60, cy - 55, TFT_BLACK);
  epaper.drawLine(cx - 18, cy - 44, cx - 60, cy - 44, TFT_BLACK);
  epaper.drawLine(cx + 18, cy - 48, cx + 60, cy - 55, TFT_BLACK);
  epaper.drawLine(cx + 18, cy - 44, cx + 60, cy - 44, TFT_BLACK);

  // Tucked paw tips barely visible at front
  epaper.fillCircle(cx - 20, cy + 68, 10, TFT_BLACK);
  epaper.fillCircle(cx - 20, cy + 68, 6, TFT_WHITE);
  epaper.fillCircle(cx + 20, cy + 68, 10, TFT_BLACK);
  epaper.fillCircle(cx + 20, cy + 68, 6, TFT_WHITE);

  // Tail wrapped around side
  for (int i = 0; i < 4; i++)
  {
    epaper.drawCircle(cx + 100, cy + 50, 35 + i, TFT_BLACK);
  }
  epaper.fillCircle(cx + 100, cy + 50, 32, TFT_WHITE);
  epaper.fillRect(cx + 10, cy + 10, 90, 65, TFT_WHITE);
  epaper.fillRect(cx + 100, cy + 50, 40, 30, TFT_WHITE);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Maximum loaf mode", cx, 420, 4);
}

// ---- Cat 9: Cat chasing butterfly ----
void drawCat9()
{
  int cx = 580, cy = 230;

  // Running body (elongated, leaning forward)
  epaper.fillCircle(cx + 20, cy + 20, 55, TFT_BLACK);
  epaper.fillCircle(cx + 20, cy + 20, 49, TFT_WHITE);

  // Head (reaching forward)
  epaper.fillCircle(cx - 60, cy - 20, 45, TFT_BLACK);
  epaper.fillCircle(cx - 60, cy - 20, 39, TFT_WHITE);

  // Connect head to body
  epaper.fillTriangle(cx - 30, cy - 5, cx + 5, cy - 5, cx - 10, cy + 20, TFT_BLACK);
  epaper.fillTriangle(cx - 27, cy - 2, cx + 2, cy - 2, cx - 10, cy + 17, TFT_WHITE);

  // Ears (alert, forward)
  epaper.fillTriangle(cx - 90, cy - 50, cx - 78, cy - 82, cx - 65, cy - 48, TFT_BLACK);
  epaper.fillTriangle(cx - 87, cy - 52, cx - 78, cy - 76, cx - 68, cy - 50, TFT_WHITE);
  epaper.fillTriangle(cx - 45, cy - 50, cx - 35, cy - 82, cx - 22, cy - 48, TFT_BLACK);
  epaper.fillTriangle(cx - 43, cy - 52, cx - 35, cy - 76, cx - 25, cy - 50, TFT_WHITE);

  // Wide excited eyes (looking up at butterfly)
  epaper.fillCircle(cx - 75, cy - 25, 10, TFT_BLACK);
  epaper.fillCircle(cx - 50, cy - 25, 10, TFT_BLACK);
  epaper.fillCircle(cx - 73, cy - 28, 4, TFT_WHITE);
  epaper.fillCircle(cx - 48, cy - 28, 4, TFT_WHITE);

  // Nose
  epaper.fillTriangle(cx - 64, cy - 8, cx - 56, cy - 8, cx - 60, cy - 3, TFT_BLACK);

  // Open mouth (excited)
  epaper.drawLine(cx - 60, cy - 3, cx - 66, cy + 4, TFT_BLACK);
  epaper.drawLine(cx - 60, cy - 3, cx - 54, cy + 4, TFT_BLACK);

  // Whiskers (forward)
  epaper.drawLine(cx - 75, cy - 10, cx - 115, cy - 20, TFT_BLACK);
  epaper.drawLine(cx - 75, cy - 6, cx - 115, cy - 6, TFT_BLACK);
  epaper.drawLine(cx - 45, cy - 10, cx - 15, cy - 25, TFT_BLACK);
  epaper.drawLine(cx - 45, cy - 6, cx - 15, cy - 10, TFT_BLACK);

  // Front legs (one forward, one back — running)
  epaper.drawLine(cx - 15, cy + 40, cx - 50, cy + 95, TFT_BLACK);
  epaper.drawLine(cx - 14, cy + 40, cx - 49, cy + 95, TFT_BLACK);
  epaper.fillCircle(cx - 52, cy + 98, 10, TFT_BLACK);
  epaper.fillCircle(cx - 52, cy + 98, 6, TFT_WHITE);
  epaper.drawLine(cx + 5, cy + 45, cx + 25, cy + 95, TFT_BLACK);
  epaper.drawLine(cx + 6, cy + 45, cx + 26, cy + 95, TFT_BLACK);
  epaper.fillCircle(cx + 26, cy + 98, 10, TFT_BLACK);
  epaper.fillCircle(cx + 26, cy + 98, 6, TFT_WHITE);

  // Back legs (extended)
  epaper.drawLine(cx + 50, cy + 35, cx + 80, cy + 95, TFT_BLACK);
  epaper.drawLine(cx + 51, cy + 35, cx + 81, cy + 95, TFT_BLACK);
  epaper.fillCircle(cx + 81, cy + 98, 10, TFT_BLACK);
  epaper.fillCircle(cx + 81, cy + 98, 6, TFT_WHITE);
  epaper.drawLine(cx + 60, cy + 25, cx + 100, cy + 85, TFT_BLACK);
  epaper.drawLine(cx + 61, cy + 25, cx + 101, cy + 85, TFT_BLACK);
  epaper.fillCircle(cx + 101, cy + 88, 10, TFT_BLACK);
  epaper.fillCircle(cx + 101, cy + 88, 6, TFT_WHITE);

  // Tail (streaming behind, wavy)
  epaper.drawLine(cx + 65, cy + 5, cx + 100, cy - 20, TFT_BLACK);
  epaper.drawLine(cx + 66, cy + 5, cx + 101, cy - 20, TFT_BLACK);
  epaper.drawLine(cx + 100, cy - 20, cx + 90, cy - 45, TFT_BLACK);
  epaper.drawLine(cx + 101, cy - 20, cx + 91, cy - 45, TFT_BLACK);
  epaper.drawLine(cx + 90, cy - 45, cx + 110, cy - 60, TFT_BLACK);
  epaper.drawLine(cx + 91, cy - 45, cx + 111, cy - 60, TFT_BLACK);

  // --- Butterfly ---
  int bx = 500, by = 100;
  // Wings (two pairs of circles)
  epaper.fillCircle(bx - 12, by - 8, 12, TFT_BLACK);
  epaper.fillCircle(bx + 12, by - 8, 12, TFT_BLACK);
  epaper.fillCircle(bx - 8, by + 6, 9, TFT_BLACK);
  epaper.fillCircle(bx + 8, by + 6, 9, TFT_BLACK);
  epaper.fillCircle(bx - 12, by - 8, 8, TFT_WHITE);
  epaper.fillCircle(bx + 12, by - 8, 8, TFT_WHITE);
  epaper.fillCircle(bx - 8, by + 6, 5, TFT_WHITE);
  epaper.fillCircle(bx + 8, by + 6, 5, TFT_WHITE);
  // Body
  epaper.drawLine(bx, by - 14, bx, by + 14, TFT_BLACK);
  epaper.drawLine(bx + 1, by - 14, bx + 1, by + 14, TFT_BLACK);
  // Antennae
  epaper.drawLine(bx, by - 14, bx - 8, by - 25, TFT_BLACK);
  epaper.drawLine(bx, by - 14, bx + 8, by - 25, TFT_BLACK);
  epaper.fillCircle(bx - 8, by - 25, 2, TFT_BLACK);
  epaper.fillCircle(bx + 8, by - 25, 2, TFT_BLACK);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Almost got it!", 600, 420, 4);
}

// ---- Cat 10: Cat with yarn ball ----
void drawCat10()
{
  int cx = 580, cy = 200;

  // Body (lying on side, relaxed)
  epaper.fillCircle(cx + 20, cy + 40, 65, TFT_BLACK);
  epaper.fillCircle(cx + 20, cy + 40, 59, TFT_WHITE);

  // Head
  epaper.fillCircle(cx - 55, cy - 10, 48, TFT_BLACK);
  epaper.fillCircle(cx - 55, cy - 10, 42, TFT_WHITE);

  // Ears
  epaper.fillTriangle(cx - 88, cy - 42, cx - 75, cy - 76, cx - 58, cy - 42, TFT_BLACK);
  epaper.fillTriangle(cx - 85, cy - 44, cx - 75, cy - 70, cx - 62, cy - 44, TFT_WHITE);
  epaper.fillTriangle(cx - 35, cy - 42, cx - 22, cy - 76, cx - 10, cy - 42, TFT_BLACK);
  epaper.fillTriangle(cx - 33, cy - 44, cx - 22, cy - 70, cx - 13, cy - 44, TFT_WHITE);

  // Mischievous eyes (looking down at yarn)
  epaper.fillCircle(cx - 70, cy - 15, 10, TFT_BLACK);
  epaper.fillCircle(cx - 42, cy - 15, 10, TFT_BLACK);
  epaper.fillCircle(cx - 68, cy - 12, 4, TFT_WHITE);
  epaper.fillCircle(cx - 40, cy - 12, 4, TFT_WHITE);

  // Nose
  epaper.fillTriangle(cx - 59, cy + 2, cx - 51, cy + 2, cx - 55, cy + 7, TFT_BLACK);

  // Cheeky grin
  epaper.drawLine(cx - 55, cy + 7, cx - 65, cy + 14, TFT_BLACK);
  epaper.drawLine(cx - 55, cy + 7, cx - 45, cy + 14, TFT_BLACK);
  epaper.drawLine(cx - 65, cy + 14, cx - 60, cy + 16, TFT_BLACK);
  epaper.drawLine(cx - 45, cy + 14, cx - 50, cy + 16, TFT_BLACK);

  // Whiskers
  epaper.drawLine(cx - 70, cy + 2, cx - 110, cy - 5, TFT_BLACK);
  epaper.drawLine(cx - 70, cy + 5, cx - 110, cy + 5, TFT_BLACK);
  epaper.drawLine(cx - 40, cy + 2, cx - 5, cy - 5, TFT_BLACK);
  epaper.drawLine(cx - 40, cy + 5, cx - 5, cy + 5, TFT_BLACK);

  // Front paws (holding yarn)
  epaper.drawLine(cx - 35, cy + 30, cx - 25, cy + 80, TFT_BLACK);
  epaper.drawLine(cx - 34, cy + 30, cx - 24, cy + 80, TFT_BLACK);
  epaper.fillCircle(cx - 25, cy + 83, 12, TFT_BLACK);
  epaper.fillCircle(cx - 25, cy + 83, 7, TFT_WHITE);
  epaper.drawLine(cx - 15, cy + 35, cx + 5, cy + 85, TFT_BLACK);
  epaper.drawLine(cx - 14, cy + 35, cx + 6, cy + 85, TFT_BLACK);
  epaper.fillCircle(cx + 6, cy + 88, 12, TFT_BLACK);
  epaper.fillCircle(cx + 6, cy + 88, 7, TFT_WHITE);

  // Back legs
  epaper.fillCircle(cx + 70, cy + 95, 14, TFT_BLACK);
  epaper.fillCircle(cx + 70, cy + 95, 9, TFT_WHITE);

  // Tail
  for (int i = 0; i < 3; i++)
  {
    epaper.drawCircle(cx + 95, cy + 10, 35 + i, TFT_BLACK);
  }
  epaper.fillCircle(cx + 95, cy + 10, 33, TFT_WHITE);
  epaper.fillRect(cx + 15, cy - 10, 80, 55, TFT_WHITE);
  epaper.fillRect(cx + 95, cy + 10, 40, 30, TFT_WHITE);

  // --- Yarn ball ---
  int yx = 690, yy = 260;
  // Ball
  epaper.fillCircle(yx, yy, 35, TFT_BLACK);
  epaper.fillCircle(yx, yy, 30, TFT_WHITE);
  // Yarn lines (curved texture)
  epaper.drawCircle(yx - 5, yy + 5, 20, TFT_BLACK);
  epaper.drawCircle(yx + 8, yy - 3, 18, TFT_BLACK);
  epaper.drawCircle(yx - 3, yy - 8, 15, TFT_BLACK);
  // Clip to ball shape
  epaper.fillRect(yx - 40, yy - 40, 5, 80, TFT_WHITE);
  epaper.fillRect(yx + 35, yy - 40, 5, 80, TFT_WHITE);
  epaper.fillRect(yx - 40, yy - 40, 80, 5, TFT_WHITE);
  epaper.fillRect(yx - 40, yy + 35, 80, 5, TFT_WHITE);
  // Redraw outer circle for clean edge
  epaper.drawCircle(yx, yy, 31, TFT_BLACK);
  epaper.drawCircle(yx, yy, 30, TFT_BLACK);

  // Trailing yarn strand from ball to paw
  epaper.drawLine(yx - 30, yy - 5, cx + 6, cy + 88, TFT_BLACK);
  epaper.drawLine(yx - 28, yy + 5, cx - 10, cy + 95, TFT_BLACK);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Mine! All mine!", 600, 420, 4);
}

// ---- Cat 11: Cat looking out window (side profile) ----
void drawCat11()
{
  int cx = 600, cy = 210;

  // Window frame
  epaper.drawRect(cx - 100, cy - 120, 200, 240, TFT_BLACK);
  epaper.drawRect(cx - 99, cy - 119, 198, 238, TFT_BLACK);
  // Window cross
  epaper.drawLine(cx, cy - 120, cx, cy + 120, TFT_BLACK);
  epaper.drawLine(cx + 1, cy - 120, cx + 1, cy + 120, TFT_BLACK);
  epaper.drawLine(cx - 100, cy, cx + 100, cy, TFT_BLACK);
  epaper.drawLine(cx - 100, cy + 1, cx + 100, cy + 1, TFT_BLACK);

  // Stars/moon visible through window (top-left pane)
  epaper.fillCircle(cx - 65, cy - 80, 15, TFT_BLACK);
  epaper.fillCircle(cx - 55, cy - 80, 14, TFT_WHITE);  // crescent moon
  // Stars
  epaper.fillCircle(cx - 30, cy - 100, 2, TFT_BLACK);
  epaper.fillCircle(cx - 80, cy - 50, 2, TFT_BLACK);
  epaper.fillCircle(cx - 45, cy - 55, 2, TFT_BLACK);
  // Top-right pane stars
  epaper.fillCircle(cx + 40, cy - 90, 2, TFT_BLACK);
  epaper.fillCircle(cx + 70, cy - 60, 2, TFT_BLACK);
  epaper.fillCircle(cx + 55, cy - 40, 2, TFT_BLACK);

  // Window sill
  epaper.fillRect(cx - 110, cy + 120, 220, 10, TFT_BLACK);
  epaper.fillRect(cx - 108, cy + 122, 216, 6, TFT_WHITE);
  epaper.drawLine(cx - 110, cy + 120, cx + 110, cy + 120, TFT_BLACK);
  epaper.drawLine(cx - 110, cy + 130, cx + 110, cy + 130, TFT_BLACK);

  // Cat silhouette on sill (sitting, facing window — back to viewer)
  // Body (dark silhouette)
  epaper.fillCircle(cx, cy + 80, 45, TFT_BLACK);

  // Head
  epaper.fillCircle(cx, cy + 30, 35, TFT_BLACK);

  // Ears (silhouette)
  epaper.fillTriangle(cx - 30, cy + 8, cx - 18, cy - 15, cx - 5, cy + 10, TFT_BLACK);
  epaper.fillTriangle(cx + 30, cy + 8, cx + 18, cy - 15, cx + 5, cy + 10, TFT_BLACK);

  // Ear inners (tiny white triangles for depth)
  epaper.fillTriangle(cx - 26, cy + 10, cx - 19, cy - 6, cx - 10, cy + 12, TFT_WHITE);
  epaper.fillTriangle(cx + 26, cy + 10, cx + 19, cy - 6, cx + 10, cy + 12, TFT_WHITE);
  // Re-fill head over ear inners
  epaper.fillCircle(cx, cy + 30, 30, TFT_BLACK);

  // Tail curling up on the right
  for (int i = 0; i < 5; i++)
  {
    epaper.drawCircle(cx + 65, cy + 60, 30 + i, TFT_BLACK);
  }
  epaper.fillCircle(cx + 65, cy + 60, 27, TFT_WHITE);
  epaper.fillRect(cx + 5, cy + 35, 60, 50, TFT_WHITE);
  // Re-fill body over cleanup
  epaper.fillCircle(cx, cy + 80, 45, TFT_BLACK);
  // Re-clean the tail arc
  epaper.fillCircle(cx + 65, cy + 60, 27, TFT_WHITE);
  epaper.fillRect(cx + 5, cy + 35, 60, 50, TFT_WHITE);
  // Draw just the visible tail portion
  for (int i = 0; i < 4; i++)
  {
    epaper.drawCircle(cx + 65, cy + 55, 30 + i, TFT_BLACK);
  }
  epaper.fillCircle(cx + 65, cy + 55, 27, TFT_WHITE);
  epaper.fillRect(cx, cy + 40, 65, 90, TFT_WHITE);
  epaper.fillRect(cx + 65, cy + 55, 40, 30, TFT_WHITE);
  // Re-draw body
  epaper.fillCircle(cx, cy + 80, 45, TFT_BLACK);
  epaper.fillCircle(cx, cy + 30, 35, TFT_BLACK);
  epaper.fillTriangle(cx - 30, cy + 8, cx - 18, cy - 15, cx - 5, cy + 10, TFT_BLACK);
  epaper.fillTriangle(cx + 30, cy + 8, cx + 18, cy - 15, cx + 5, cy + 10, TFT_BLACK);
  // Simple visible tail line
  epaper.drawLine(cx + 40, cy + 95, cx + 80, cy + 60, TFT_BLACK);
  epaper.drawLine(cx + 41, cy + 95, cx + 81, cy + 60, TFT_BLACK);
  epaper.drawLine(cx + 42, cy + 95, cx + 82, cy + 60, TFT_BLACK);
  epaper.drawLine(cx + 80, cy + 60, cx + 75, cy + 40, TFT_BLACK);
  epaper.drawLine(cx + 81, cy + 60, cx + 76, cy + 40, TFT_BLACK);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Dreaming of birds...", 600, 420, 4);
}

// ---- Cat 12: Cat knocking cup off table ----
void drawCat12()
{
  int cx = 580, cy = 200;

  // Table surface
  epaper.fillRect(420, cy + 80, 360, 6, TFT_BLACK);
  // Table legs
  epaper.fillRect(430, cy + 86, 8, 60, TFT_BLACK);
  epaper.fillRect(760, cy + 86, 8, 60, TFT_BLACK);

  // Cat body (sitting on table)
  epaper.fillCircle(cx, cy + 30, 55, TFT_BLACK);
  epaper.fillCircle(cx, cy + 30, 49, TFT_WHITE);

  // Head
  epaper.fillCircle(cx, cy - 35, 45, TFT_BLACK);
  epaper.fillCircle(cx, cy - 35, 39, TFT_WHITE);

  // Ears
  epaper.fillTriangle(cx - 38, cy - 65, cx - 22, cy - 98, cx - 8, cy - 60, TFT_BLACK);
  epaper.fillTriangle(cx - 34, cy - 67, cx - 23, cy - 92, cx - 12, cy - 63, TFT_WHITE);
  epaper.fillTriangle(cx + 38, cy - 65, cx + 22, cy - 98, cx + 8, cy - 60, TFT_BLACK);
  epaper.fillTriangle(cx + 34, cy - 67, cx + 23, cy - 92, cx + 12, cy - 63, TFT_WHITE);

  // Sly eyes (looking at cup)
  epaper.fillCircle(cx - 16, cy - 40, 8, TFT_BLACK);
  epaper.fillCircle(cx + 16, cy - 40, 8, TFT_BLACK);
  epaper.fillCircle(cx - 12, cy - 41, 3, TFT_WHITE);
  epaper.fillCircle(cx + 20, cy - 41, 3, TFT_WHITE);

  // Smirk
  epaper.fillTriangle(cx - 3, cy - 22, cx + 3, cy - 22, cx, cy - 18, TFT_BLACK);
  epaper.drawLine(cx, cy - 18, cx + 10, cy - 14, TFT_BLACK);

  // Whiskers
  epaper.drawLine(cx - 18, cy - 25, cx - 55, cy - 32, TFT_BLACK);
  epaper.drawLine(cx - 18, cy - 22, cx - 55, cy - 22, TFT_BLACK);
  epaper.drawLine(cx + 18, cy - 25, cx + 55, cy - 32, TFT_BLACK);
  epaper.drawLine(cx + 18, cy - 22, cx + 55, cy - 22, TFT_BLACK);

  // Extended paw pushing cup
  epaper.drawLine(cx + 45, cy + 10, cx + 110, cy + 50, TFT_BLACK);
  epaper.drawLine(cx + 46, cy + 10, cx + 111, cy + 50, TFT_BLACK);
  epaper.fillCircle(cx + 113, cy + 53, 10, TFT_BLACK);
  epaper.fillCircle(cx + 113, cy + 53, 6, TFT_WHITE);

  // Cup (teetering on edge)
  int cupX = 720, cupY = cy + 45;
  epaper.drawLine(cupX - 12, cupY, cupX - 8, cupY + 35, TFT_BLACK);
  epaper.drawLine(cupX + 12, cupY, cupX + 8, cupY + 35, TFT_BLACK);
  epaper.drawLine(cupX - 8, cupY + 35, cupX + 8, cupY + 35, TFT_BLACK);
  epaper.drawLine(cupX - 12, cupY, cupX + 12, cupY, TFT_BLACK);
  // Cup handle
  for (int i = 0; i < 2; i++)
    epaper.drawCircle(cupX + 15, cupY + 15, 7 + i, TFT_BLACK);
  epaper.fillRect(cupX + 8, cupY + 8, 7, 14, TFT_WHITE);

  // Front paw (other)
  epaper.fillCircle(cx - 20, cy + 75, 14, TFT_BLACK);
  epaper.fillCircle(cx - 20, cy + 75, 9, TFT_WHITE);

  // Tail
  for (int i = 0; i < 3; i++)
    epaper.drawCircle(cx - 65, cy + 10, 35 + i, TFT_BLACK);
  epaper.fillCircle(cx - 65, cy + 10, 33, TFT_WHITE);
  epaper.fillRect(cx - 65, cy - 5, 70, 40, TFT_WHITE);
  epaper.fillRect(cx - 65, cy + 10, 30, 30, TFT_WHITE);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Oops... gravity test!", 600, 420, 4);
}

// ---- Cat 13: Fancy cat with bow tie ----
void drawCat13()
{
  int cx = 600, cy = 200;

  // Body
  epaper.fillCircle(cx, cy + 60, 70, TFT_BLACK);
  epaper.fillCircle(cx, cy + 60, 64, TFT_WHITE);

  // Head
  epaper.fillCircle(cx, cy - 40, 55, TFT_BLACK);
  epaper.fillCircle(cx, cy - 40, 49, TFT_WHITE);

  // Ears
  epaper.fillTriangle(cx - 45, cy - 75, cx - 25, cy - 110, cx - 10, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx - 40, cy - 78, cx - 27, cy - 102, cx - 15, cy - 70, TFT_WHITE);
  epaper.fillTriangle(cx + 45, cy - 75, cx + 25, cy - 110, cx + 10, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx + 40, cy - 78, cx + 27, cy - 102, cx + 15, cy - 70, TFT_WHITE);

  // Sophisticated half-closed eyes
  epaper.drawLine(cx - 28, cy - 48, cx - 18, cy - 52, TFT_BLACK);
  epaper.drawLine(cx - 18, cy - 52, cx - 8, cy - 48, TFT_BLACK);
  epaper.drawLine(cx - 27, cy - 47, cx - 18, cy - 50, TFT_BLACK);
  epaper.drawLine(cx - 18, cy - 50, cx - 9, cy - 47, TFT_BLACK);
  epaper.drawLine(cx + 8, cy - 48, cx + 18, cy - 52, TFT_BLACK);
  epaper.drawLine(cx + 18, cy - 52, cx + 28, cy - 48, TFT_BLACK);
  epaper.drawLine(cx + 9, cy - 47, cx + 18, cy - 50, TFT_BLACK);
  epaper.drawLine(cx + 18, cy - 50, cx + 27, cy - 47, TFT_BLACK);

  // Nose
  epaper.fillTriangle(cx - 4, cy - 28, cx + 4, cy - 28, cx, cy - 23, TFT_BLACK);

  // Refined smile
  epaper.drawLine(cx, cy - 23, cx - 8, cy - 17, TFT_BLACK);
  epaper.drawLine(cx, cy - 23, cx + 8, cy - 17, TFT_BLACK);

  // Whiskers (elegant, slightly upturned)
  epaper.drawLine(cx - 20, cy - 28, cx - 65, cy - 38, TFT_BLACK);
  epaper.drawLine(cx - 20, cy - 24, cx - 65, cy - 28, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 28, cx + 65, cy - 38, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 24, cx + 65, cy - 28, TFT_BLACK);

  // Bow tie at neck
  int btx = cx, bty = cy + 5;
  epaper.fillTriangle(btx, bty, btx - 25, bty - 14, btx - 25, bty + 14, TFT_BLACK);
  epaper.fillTriangle(btx, bty, btx + 25, bty - 14, btx + 25, bty + 14, TFT_BLACK);
  epaper.fillCircle(btx, bty, 6, TFT_BLACK);
  epaper.fillCircle(btx, bty, 3, TFT_WHITE);

  // Front paws (neatly together)
  epaper.fillCircle(cx - 20, cy + 120, 18, TFT_BLACK);
  epaper.fillCircle(cx - 20, cy + 120, 13, TFT_WHITE);
  epaper.fillCircle(cx + 20, cy + 120, 18, TFT_BLACK);
  epaper.fillCircle(cx + 20, cy + 120, 13, TFT_WHITE);

  // Tail (elegantly draped)
  for (int i = 0; i < 3; i++)
    epaper.drawCircle(cx + 85, cy + 70, 40 + i, TFT_BLACK);
  epaper.fillCircle(cx + 85, cy + 70, 38, TFT_WHITE);
  epaper.fillRect(cx - 5, cy + 35, 90, 70, TFT_WHITE);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Quite distinguished", cx, 420, 4);
}

// ---- Cat 14: Cat hanging from ledge ----
void drawCat14()
{
  int cx = 600, cy = 160;

  // Ledge at top
  epaper.fillRect(420, cy - 50, 360, 10, TFT_BLACK);

  // Two paws gripping ledge
  epaper.fillCircle(cx - 30, cy - 45, 16, TFT_BLACK);
  epaper.fillCircle(cx - 30, cy - 45, 11, TFT_WHITE);
  epaper.fillCircle(cx + 30, cy - 45, 16, TFT_BLACK);
  epaper.fillCircle(cx + 30, cy - 45, 11, TFT_WHITE);
  // Claws
  for (int d = -6; d <= 6; d += 4)
  {
    epaper.drawLine(cx - 30 + d, cy - 56, cx - 30 + d, cy - 62, TFT_BLACK);
    epaper.drawLine(cx + 30 + d, cy - 56, cx + 30 + d, cy - 62, TFT_BLACK);
  }

  // Arms
  epaper.drawLine(cx - 30, cy - 30, cx - 25, cy + 5, TFT_BLACK);
  epaper.drawLine(cx - 29, cy - 30, cx - 24, cy + 5, TFT_BLACK);
  epaper.drawLine(cx + 30, cy - 30, cx + 25, cy + 5, TFT_BLACK);
  epaper.drawLine(cx + 29, cy - 30, cx + 24, cy + 5, TFT_BLACK);

  // Body (dangling)
  epaper.fillCircle(cx, cy + 50, 55, TFT_BLACK);
  epaper.fillCircle(cx, cy + 50, 49, TFT_WHITE);

  // Head
  epaper.fillCircle(cx, cy + 10, 42, TFT_BLACK);
  epaper.fillCircle(cx, cy + 10, 36, TFT_WHITE);

  // Ears
  epaper.fillTriangle(cx - 35, cy - 15, cx - 22, cy - 42, cx - 8, cy - 12, TFT_BLACK);
  epaper.fillTriangle(cx - 32, cy - 17, cx - 22, cy - 36, cx - 12, cy - 15, TFT_WHITE);
  epaper.fillTriangle(cx + 35, cy - 15, cx + 22, cy - 42, cx + 8, cy - 12, TFT_BLACK);
  epaper.fillTriangle(cx + 32, cy - 17, cx + 22, cy - 36, cx + 12, cy - 15, TFT_WHITE);

  // Wide worried eyes
  epaper.fillCircle(cx - 15, cy + 5, 11, TFT_BLACK);
  epaper.fillCircle(cx + 15, cy + 5, 11, TFT_BLACK);
  epaper.fillCircle(cx - 15, cy + 5, 6, TFT_WHITE);
  epaper.fillCircle(cx + 15, cy + 5, 6, TFT_WHITE);
  epaper.fillCircle(cx - 14, cy + 3, 3, TFT_BLACK);
  epaper.fillCircle(cx + 16, cy + 3, 3, TFT_BLACK);

  // Worried mouth
  epaper.drawLine(cx - 8, cy + 22, cx, cy + 26, TFT_BLACK);
  epaper.drawLine(cx, cy + 26, cx + 8, cy + 22, TFT_BLACK);

  // Dangling back legs
  epaper.drawLine(cx - 20, cy + 95, cx - 25, cy + 140, TFT_BLACK);
  epaper.drawLine(cx - 19, cy + 95, cx - 24, cy + 140, TFT_BLACK);
  epaper.fillCircle(cx - 25, cy + 143, 10, TFT_BLACK);
  epaper.fillCircle(cx - 25, cy + 143, 6, TFT_WHITE);
  epaper.drawLine(cx + 20, cy + 95, cx + 25, cy + 140, TFT_BLACK);
  epaper.drawLine(cx + 21, cy + 95, cx + 26, cy + 140, TFT_BLACK);
  epaper.fillCircle(cx + 25, cy + 143, 10, TFT_BLACK);
  epaper.fillCircle(cx + 25, cy + 143, 6, TFT_WHITE);

  // Tail (dangling)
  epaper.drawLine(cx + 45, cy + 80, cx + 55, cy + 140, TFT_BLACK);
  epaper.drawLine(cx + 46, cy + 80, cx + 56, cy + 140, TFT_BLACK);
  epaper.drawLine(cx + 55, cy + 140, cx + 45, cy + 155, TFT_BLACK);
  epaper.drawLine(cx + 56, cy + 140, cx + 46, cy + 155, TFT_BLACK);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Help... please?", cx, 420, 4);
}

// ---- Cat 15: Mama cat with kitten ----
void drawCat15()
{
  int cx = 570, cy = 210;

  // Mama body
  epaper.fillCircle(cx, cy + 50, 65, TFT_BLACK);
  epaper.fillCircle(cx, cy + 50, 59, TFT_WHITE);

  // Mama head
  epaper.fillCircle(cx - 10, cy - 25, 48, TFT_BLACK);
  epaper.fillCircle(cx - 10, cy - 25, 42, TFT_WHITE);

  // Mama ears
  epaper.fillTriangle(cx - 48, cy - 58, cx - 35, cy - 90, cx - 18, cy - 55, TFT_BLACK);
  epaper.fillTriangle(cx - 44, cy - 60, cx - 35, cy - 84, cx - 22, cy - 58, TFT_WHITE);
  epaper.fillTriangle(cx + 18, cy - 58, cx + 28, cy - 90, cx + 42, cy - 55, TFT_BLACK);
  epaper.fillTriangle(cx + 22, cy - 60, cx + 28, cy - 84, cx + 38, cy - 58, TFT_WHITE);

  // Mama gentle eyes
  epaper.drawLine(cx - 28, cy - 28, cx - 18, cy - 34, TFT_BLACK);
  epaper.drawLine(cx - 18, cy - 34, cx - 8, cy - 28, TFT_BLACK);
  epaper.drawLine(cx + 2, cy - 28, cx + 12, cy - 34, TFT_BLACK);
  epaper.drawLine(cx + 12, cy - 34, cx + 22, cy - 28, TFT_BLACK);

  // Mama nose
  epaper.fillTriangle(cx - 13, cy - 14, cx - 7, cy - 14, cx - 10, cy - 10, TFT_BLACK);

  // Mama smile
  epaper.drawLine(cx - 10, cy - 10, cx - 16, cy - 5, TFT_BLACK);
  epaper.drawLine(cx - 10, cy - 10, cx - 4, cy - 5, TFT_BLACK);

  // Mama whiskers
  epaper.drawLine(cx - 25, cy - 14, cx - 60, cy - 22, TFT_BLACK);
  epaper.drawLine(cx - 25, cy - 10, cx - 60, cy - 10, TFT_BLACK);
  epaper.drawLine(cx + 5, cy - 14, cx + 40, cy - 22, TFT_BLACK);
  epaper.drawLine(cx + 5, cy - 10, cx + 40, cy - 10, TFT_BLACK);

  // Mama paws
  epaper.fillCircle(cx - 30, cy + 105, 16, TFT_BLACK);
  epaper.fillCircle(cx - 30, cy + 105, 11, TFT_WHITE);
  epaper.fillCircle(cx + 20, cy + 105, 16, TFT_BLACK);
  epaper.fillCircle(cx + 20, cy + 105, 11, TFT_WHITE);

  // Mama tail (wrapped protectively)
  for (int i = 0; i < 4; i++)
    epaper.drawCircle(cx + 80, cy + 60, 35 + i, TFT_BLACK);
  epaper.fillCircle(cx + 80, cy + 60, 32, TFT_WHITE);
  epaper.fillRect(cx, cy + 25, 80, 65, TFT_WHITE);

  // --- Kitten (tiny, snuggled against mama) ---
  int kx = cx + 65, ky = cy + 60;

  // Kitten body
  epaper.fillCircle(kx, ky + 10, 25, TFT_BLACK);
  epaper.fillCircle(kx, ky + 10, 21, TFT_WHITE);

  // Kitten head
  epaper.fillCircle(kx + 5, ky - 15, 18, TFT_BLACK);
  epaper.fillCircle(kx + 5, ky - 15, 14, TFT_WHITE);

  // Kitten ears (tiny)
  epaper.fillTriangle(kx - 8, ky - 27, kx - 2, ky - 40, kx + 2, ky - 25, TFT_BLACK);
  epaper.fillTriangle(kx - 6, ky - 28, kx - 2, ky - 36, kx + 0, ky - 27, TFT_WHITE);
  epaper.fillTriangle(kx + 10, ky - 27, kx + 16, ky - 40, kx + 20, ky - 25, TFT_BLACK);
  epaper.fillTriangle(kx + 12, ky - 28, kx + 16, ky - 36, kx + 18, ky - 27, TFT_WHITE);

  // Kitten closed eyes (sleeping)
  epaper.drawLine(kx - 2, ky - 17, kx + 3, ky - 19, TFT_BLACK);
  epaper.drawLine(kx + 3, ky - 19, kx + 8, ky - 17, TFT_BLACK);

  // Kitten tiny nose
  epaper.fillCircle(kx + 5, ky - 11, 2, TFT_BLACK);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("My little one", 600, 420, 4);
}

// ---- Cat 16: Cat in a paper bag ----
void drawCat16()
{
  int cx = 600, cy = 200;

  // Paper bag body
  int bx = cx - 60, by = cy - 30, bw = 120, bh = 160;
  epaper.drawRect(bx, by, bw, bh, TFT_BLACK);
  epaper.drawRect(bx + 1, by + 1, bw - 2, bh - 2, TFT_BLACK);
  // Bag crumpled top
  epaper.drawLine(bx, by, bx + 15, by - 15, TFT_BLACK);
  epaper.drawLine(bx + 15, by - 15, bx + 35, by - 5, TFT_BLACK);
  epaper.drawLine(bx + 35, by - 5, bx + 55, by - 18, TFT_BLACK);
  epaper.drawLine(bx + 55, by - 18, bx + 75, by - 8, TFT_BLACK);
  epaper.drawLine(bx + 75, by - 8, bx + 95, by - 20, TFT_BLACK);
  epaper.drawLine(bx + 95, by - 20, bx + bw, by, TFT_BLACK);
  // Crinkle lines on bag
  epaper.drawLine(bx + 20, by + 40, bx + 25, by + 80, TFT_BLACK);
  epaper.drawLine(bx + bw - 20, by + 30, bx + bw - 25, by + 70, TFT_BLACK);

  // Cat ears poking out above bag
  epaper.fillTriangle(cx - 30, by - 10, cx - 18, by - 50, cx - 5, by - 8, TFT_BLACK);
  epaper.fillTriangle(cx - 27, by - 12, cx - 18, by - 44, cx - 8, by - 11, TFT_WHITE);
  epaper.fillTriangle(cx + 5, by - 8, cx + 18, by - 50, cx + 30, by - 10, TFT_BLACK);
  epaper.fillTriangle(cx + 8, by - 11, cx + 18, by - 44, cx + 27, by - 12, TFT_WHITE);

  // Eyes peeking over bag top (just the top half visible)
  int eyeY = by + 10;
  epaper.fillCircle(cx - 18, eyeY, 14, TFT_BLACK);
  epaper.fillCircle(cx + 18, eyeY, 14, TFT_BLACK);
  epaper.fillCircle(cx - 18, eyeY, 9, TFT_WHITE);
  epaper.fillCircle(cx + 18, eyeY, 9, TFT_WHITE);
  epaper.fillCircle(cx - 16, eyeY - 2, 4, TFT_BLACK);
  epaper.fillCircle(cx + 20, eyeY - 2, 4, TFT_BLACK);
  // White over bag line to hide bottom of eyes
  epaper.fillRect(bx + 2, by + 20, bw - 4, bh - 22, TFT_WHITE);

  // Bag base
  epaper.drawLine(bx, by + bh, bx + bw, by + bh, TFT_BLACK);

  // Paw tips at bag bottom
  epaper.fillCircle(bx + 25, by + bh + 5, 10, TFT_BLACK);
  epaper.fillCircle(bx + 25, by + bh + 5, 6, TFT_WHITE);
  epaper.fillCircle(bx + bw - 25, by + bh + 5, 10, TFT_BLACK);
  epaper.fillCircle(bx + bw - 25, by + bh + 5, 6, TFT_WHITE);

  // Tail sticking out side
  epaper.drawLine(bx + bw, by + bh - 30, bx + bw + 40, by + bh - 50, TFT_BLACK);
  epaper.drawLine(bx + bw, by + bh - 29, bx + bw + 40, by + bh - 49, TFT_BLACK);
  epaper.drawLine(bx + bw + 40, by + bh - 50, bx + bw + 35, by + bh - 70, TFT_BLACK);
  epaper.drawLine(bx + bw + 40, by + bh - 49, bx + bw + 35, by + bh - 69, TFT_BLACK);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("You can't see me", cx, 420, 4);
}

// ---- Cat 17: Chonky cat ----
void drawCat17()
{
  int cx = 600, cy = 210;

  // Very round body
  epaper.fillCircle(cx, cy + 30, 95, TFT_BLACK);
  epaper.fillCircle(cx, cy + 30, 88, TFT_WHITE);

  // Head (smaller in comparison)
  epaper.fillCircle(cx, cy - 65, 42, TFT_BLACK);
  epaper.fillCircle(cx, cy - 65, 36, TFT_WHITE);

  // Ears
  epaper.fillTriangle(cx - 35, cy - 92, cx - 22, cy - 122, cx - 8, cy - 88, TFT_BLACK);
  epaper.fillTriangle(cx - 32, cy - 94, cx - 22, cy - 116, cx - 12, cy - 90, TFT_WHITE);
  epaper.fillTriangle(cx + 35, cy - 92, cx + 22, cy - 122, cx + 8, cy - 88, TFT_BLACK);
  epaper.fillTriangle(cx + 32, cy - 94, cx + 22, cy - 116, cx + 12, cy - 90, TFT_WHITE);

  // Content eyes
  epaper.fillCircle(cx - 16, cy - 70, 8, TFT_BLACK);
  epaper.fillCircle(cx + 16, cy - 70, 8, TFT_BLACK);
  epaper.fillCircle(cx - 14, cy - 72, 3, TFT_WHITE);
  epaper.fillCircle(cx + 18, cy - 72, 3, TFT_WHITE);

  // Nose
  epaper.fillTriangle(cx - 3, cy - 55, cx + 3, cy - 55, cx, cy - 51, TFT_BLACK);

  // Happy mouth
  epaper.drawLine(cx, cy - 51, cx - 8, cy - 45, TFT_BLACK);
  epaper.drawLine(cx, cy - 51, cx + 8, cy - 45, TFT_BLACK);

  // Whiskers
  epaper.drawLine(cx - 16, cy - 55, cx - 50, cy - 62, TFT_BLACK);
  epaper.drawLine(cx - 16, cy - 52, cx - 50, cy - 52, TFT_BLACK);
  epaper.drawLine(cx + 16, cy - 55, cx + 50, cy - 62, TFT_BLACK);
  epaper.drawLine(cx + 16, cy - 52, cx + 50, cy - 52, TFT_BLACK);

  // Tiny paws (barely visible under round body)
  epaper.fillCircle(cx - 35, cy + 115, 14, TFT_BLACK);
  epaper.fillCircle(cx - 35, cy + 115, 9, TFT_WHITE);
  epaper.fillCircle(cx + 35, cy + 115, 14, TFT_BLACK);
  epaper.fillCircle(cx + 35, cy + 115, 9, TFT_WHITE);

  // Belly stripes (tiger pattern)
  for (int i = -2; i <= 2; i++)
  {
    int sy = cy + 30 + i * 25;
    epaper.drawLine(cx - 30, sy, cx - 15, sy - 8, TFT_BLACK);
    epaper.drawLine(cx + 30, sy, cx + 15, sy - 8, TFT_BLACK);
  }

  // Short tail
  epaper.drawLine(cx + 80, cy + 60, cx + 105, cy + 40, TFT_BLACK);
  epaper.drawLine(cx + 81, cy + 60, cx + 106, cy + 40, TFT_BLACK);
  epaper.drawLine(cx + 82, cy + 60, cx + 107, cy + 40, TFT_BLACK);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("More treats please", cx, 420, 4);
}

// ---- Cat 18: Cat peeking from behind wall ----
void drawCat18()
{
  int cx = 500, cy = 200;

  // Wall (right side of panel)
  epaper.fillRect(420, 0, 100, 480, TFT_BLACK);
  epaper.fillRect(425, 5, 90, 470, TFT_WHITE);
  // Wall edge
  epaper.drawLine(520, 0, 520, 480, TFT_BLACK);
  epaper.drawLine(521, 0, 521, 480, TFT_BLACK);

  // Half of cat head peeking around wall
  int hx = 545, hy = 200;

  // Half head (right half visible)
  epaper.fillCircle(hx, hy, 55, TFT_BLACK);
  epaper.fillCircle(hx, hy, 49, TFT_WHITE);
  // Hide left half behind wall
  epaper.fillRect(420, hy - 60, 103, 120, TFT_WHITE);
  epaper.drawLine(520, hy - 55, 520, hy + 55, TFT_BLACK);
  epaper.drawLine(521, hy - 55, 521, hy + 55, TFT_BLACK);

  // One ear (right side)
  epaper.fillTriangle(hx + 15, hy - 42, hx + 28, hy - 78, hx + 45, hy - 38, TFT_BLACK);
  epaper.fillTriangle(hx + 19, hy - 44, hx + 28, hy - 72, hx + 41, hy - 41, TFT_WHITE);

  // Half ear peeking (left side, just tip above wall)
  epaper.fillTriangle(520, hy - 42, 528, hy - 75, 538, hy - 38, TFT_BLACK);
  epaper.fillTriangle(522, hy - 44, 528, hy - 69, 536, hy - 41, TFT_WHITE);

  // One full eye (right)
  epaper.fillCircle(hx + 20, hy - 8, 14, TFT_BLACK);
  epaper.fillCircle(hx + 20, hy - 8, 9, TFT_WHITE);
  epaper.fillCircle(hx + 18, hy - 10, 4, TFT_BLACK);

  // Half eye (left, peeking at wall edge)
  epaper.fillCircle(525, hy - 8, 12, TFT_BLACK);
  epaper.fillCircle(525, hy - 8, 7, TFT_WHITE);
  epaper.fillCircle(527, hy - 10, 3, TFT_BLACK);
  // Clip to wall
  epaper.fillRect(420, hy - 25, 103, 40, TFT_WHITE);
  epaper.drawLine(520, hy - 20, 520, hy + 10, TFT_BLACK);
  epaper.drawLine(521, hy - 20, 521, hy + 10, TFT_BLACK);
  // Redraw partial eye
  epaper.fillCircle(528, hy - 8, 10, TFT_BLACK);
  epaper.fillCircle(528, hy - 8, 6, TFT_WHITE);
  epaper.fillCircle(530, hy - 10, 3, TFT_BLACK);
  epaper.fillRect(420, hy - 20, 108, 30, TFT_WHITE);
  epaper.drawLine(520, hy - 20, 520, hy + 10, TFT_BLACK);
  epaper.drawLine(521, hy - 20, 521, hy + 10, TFT_BLACK);

  // Just draw the visible eye simply
  epaper.fillCircle(hx + 22, hy - 5, 14, TFT_BLACK);
  epaper.fillCircle(hx + 22, hy - 5, 9, TFT_WHITE);
  epaper.fillCircle(hx + 20, hy - 7, 4, TFT_BLACK);

  // Nose (half visible)
  epaper.fillTriangle(hx - 2, hy + 12, hx + 6, hy + 12, hx + 2, hy + 17, TFT_BLACK);

  // Whiskers (right side only)
  epaper.drawLine(hx + 10, hy + 14, hx + 65, hy + 5, TFT_BLACK);
  epaper.drawLine(hx + 10, hy + 17, hx + 65, hy + 17, TFT_BLACK);
  epaper.drawLine(hx + 10, hy + 20, hx + 65, hy + 30, TFT_BLACK);

  // Paw gripping wall edge
  epaper.fillCircle(522, hy + 50, 14, TFT_BLACK);
  epaper.fillCircle(522, hy + 50, 9, TFT_WHITE);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("I see you...", 650, 420, 4);
}

// ---- Cat 19: Cat with mouse toy ----
void drawCat19()
{
  int cx = 600, cy = 200;

  // Body (crouched, hunting pose)
  epaper.fillCircle(cx, cy + 50, 60, TFT_BLACK);
  epaper.fillCircle(cx, cy + 50, 54, TFT_WHITE);

  // Head (low, focused)
  epaper.fillCircle(cx - 20, cy - 15, 48, TFT_BLACK);
  epaper.fillCircle(cx - 20, cy - 15, 42, TFT_WHITE);

  // Ears (alert, forward)
  epaper.fillTriangle(cx - 55, cy - 48, cx - 42, cy - 80, cx - 28, cy - 45, TFT_BLACK);
  epaper.fillTriangle(cx - 52, cy - 50, cx - 42, cy - 74, cx - 32, cy - 48, TFT_WHITE);
  epaper.fillTriangle(cx + 5, cy - 48, cx + 15, cy - 80, cx + 28, cy - 45, TFT_BLACK);
  epaper.fillTriangle(cx + 8, cy - 50, cx + 15, cy - 74, cx + 25, cy - 48, TFT_WHITE);

  // Focused eyes (dilated pupils)
  epaper.fillCircle(cx - 35, cy - 20, 12, TFT_BLACK);
  epaper.fillCircle(cx - 5, cy - 20, 12, TFT_BLACK);
  epaper.fillCircle(cx - 35, cy - 20, 7, TFT_WHITE);
  epaper.fillCircle(cx - 5, cy - 20, 7, TFT_WHITE);
  // Big pupils
  epaper.fillCircle(cx - 33, cy - 20, 5, TFT_BLACK);
  epaper.fillCircle(cx - 3, cy - 20, 5, TFT_BLACK);

  // Nose
  epaper.fillTriangle(cx - 23, cy - 3, cx - 17, cy - 3, cx - 20, cy + 2, TFT_BLACK);

  // Whiskers (forward, tense)
  epaper.drawLine(cx - 35, cy - 2, cx - 80, cy - 12, TFT_BLACK);
  epaper.drawLine(cx - 35, cy + 1, cx - 80, cy + 1, TFT_BLACK);
  epaper.drawLine(cx - 5, cy - 2, cx + 35, cy - 12, TFT_BLACK);
  epaper.drawLine(cx - 5, cy + 1, cx + 35, cy + 1, TFT_BLACK);

  // Crouched front paws
  epaper.fillCircle(cx - 35, cy + 100, 14, TFT_BLACK);
  epaper.fillCircle(cx - 35, cy + 100, 9, TFT_WHITE);
  epaper.fillCircle(cx + 10, cy + 100, 14, TFT_BLACK);
  epaper.fillCircle(cx + 10, cy + 100, 9, TFT_WHITE);

  // Wiggling butt (motion lines)
  epaper.drawLine(cx + 65, cy + 30, cx + 80, cy + 25, TFT_BLACK);
  epaper.drawLine(cx + 65, cy + 40, cx + 82, cy + 40, TFT_BLACK);
  epaper.drawLine(cx + 65, cy + 50, cx + 80, cy + 55, TFT_BLACK);

  // Tail (high, twitching)
  epaper.drawLine(cx + 55, cy + 30, cx + 80, cy - 30, TFT_BLACK);
  epaper.drawLine(cx + 56, cy + 30, cx + 81, cy - 30, TFT_BLACK);
  epaper.drawLine(cx + 80, cy - 30, cx + 70, cy - 45, TFT_BLACK);
  epaper.drawLine(cx + 81, cy - 30, cx + 71, cy - 45, TFT_BLACK);

  // --- Mouse toy ---
  int mx = 470, my = cy + 60;
  // Mouse body
  epaper.fillCircle(mx, my, 15, TFT_BLACK);
  epaper.fillCircle(mx, my, 11, TFT_WHITE);
  epaper.fillCircle(mx - 8, my, 12, TFT_BLACK);
  epaper.fillCircle(mx - 8, my, 8, TFT_WHITE);
  // Ear
  epaper.fillCircle(mx + 5, my - 12, 6, TFT_BLACK);
  epaper.fillCircle(mx + 5, my - 12, 3, TFT_WHITE);
  // Eye
  epaper.fillCircle(mx - 12, my - 3, 2, TFT_BLACK);
  // Tail
  epaper.drawLine(mx + 14, my + 2, mx + 35, my - 8, TFT_BLACK);
  epaper.drawLine(mx + 35, my - 8, mx + 28, my + 5, TFT_BLACK);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Target acquired...", 600, 420, 4);
}

// ---- Cat 20: Cat grooming (licking paw) ----
void drawCat20()
{
  int cx = 600, cy = 200;

  // Body
  epaper.fillCircle(cx, cy + 60, 70, TFT_BLACK);
  epaper.fillCircle(cx, cy + 60, 64, TFT_WHITE);

  // Head (tilted slightly)
  epaper.fillCircle(cx - 10, cy - 35, 50, TFT_BLACK);
  epaper.fillCircle(cx - 10, cy - 35, 44, TFT_WHITE);

  // Ears
  epaper.fillTriangle(cx - 50, cy - 68, cx - 35, cy - 102, cx - 18, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx - 46, cy - 70, cx - 35, cy - 96, cx - 22, cy - 68, TFT_WHITE);
  epaper.fillTriangle(cx + 22, cy - 68, cx + 32, cy - 102, cx + 45, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx + 25, cy - 70, cx + 32, cy - 96, cx + 41, cy - 68, TFT_WHITE);

  // Closed eyes (content)
  epaper.drawLine(cx - 28, cy - 40, cx - 18, cy - 44, TFT_BLACK);
  epaper.drawLine(cx - 18, cy - 44, cx - 8, cy - 40, TFT_BLACK);
  epaper.drawLine(cx + 2, cy - 40, cx + 12, cy - 44, TFT_BLACK);
  epaper.drawLine(cx + 12, cy - 44, cx + 22, cy - 40, TFT_BLACK);

  // Nose
  epaper.fillTriangle(cx - 13, cy - 23, cx - 7, cy - 23, cx - 10, cy - 19, TFT_BLACK);

  // Tongue (licking paw, small pink-ish area shown as outline)
  epaper.drawLine(cx - 10, cy - 19, cx + 15, cy - 5, TFT_BLACK);
  epaper.drawLine(cx - 8, cy - 17, cx + 15, cy - 3, TFT_BLACK);

  // Whiskers
  epaper.drawLine(cx - 25, cy - 22, cx - 60, cy - 30, TFT_BLACK);
  epaper.drawLine(cx - 25, cy - 19, cx - 60, cy - 19, TFT_BLACK);
  epaper.drawLine(cx + 5, cy - 22, cx + 40, cy - 30, TFT_BLACK);
  epaper.drawLine(cx + 5, cy - 19, cx + 40, cy - 19, TFT_BLACK);

  // Raised paw (being licked)
  epaper.drawLine(cx + 35, cy + 20, cx + 30, cy - 10, TFT_BLACK);
  epaper.drawLine(cx + 36, cy + 20, cx + 31, cy - 10, TFT_BLACK);
  epaper.fillCircle(cx + 25, cy - 12, 16, TFT_BLACK);
  epaper.fillCircle(cx + 25, cy - 12, 11, TFT_WHITE);
  // Toe beans
  epaper.fillCircle(cx + 20, cy - 22, 3, TFT_BLACK);
  epaper.fillCircle(cx + 28, cy - 23, 3, TFT_BLACK);
  epaper.fillCircle(cx + 34, cy - 18, 3, TFT_BLACK);
  epaper.fillCircle(cx + 25, cy - 12, 4, TFT_BLACK);

  // Other front paw
  epaper.fillCircle(cx - 25, cy + 120, 18, TFT_BLACK);
  epaper.fillCircle(cx - 25, cy + 120, 13, TFT_WHITE);

  // Tail
  for (int i = 0; i < 3; i++)
    epaper.drawCircle(cx + 80, cy + 75, 35 + i, TFT_BLACK);
  epaper.fillCircle(cx + 80, cy + 75, 33, TFT_WHITE);
  epaper.fillRect(cx - 5, cy + 40, 85, 65, TFT_WHITE);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Gotta stay clean", cx, 420, 4);
}

// ---- Cat 21: Cat on its back (belly up) ----
void drawCat21()
{
  int cx = 600, cy = 230;

  // Body (on back, round belly up)
  epaper.fillCircle(cx, cy, 75, TFT_BLACK);
  epaper.fillCircle(cx, cy, 68, TFT_WHITE);

  // Head (upside down perspective, at bottom)
  epaper.fillCircle(cx, cy + 80, 42, TFT_BLACK);
  epaper.fillCircle(cx, cy + 80, 36, TFT_WHITE);

  // Ears (pointing down since upside down)
  epaper.fillTriangle(cx - 35, cy + 108, cx - 25, cy + 132, cx - 10, cy + 105, TFT_BLACK);
  epaper.fillTriangle(cx - 32, cy + 110, cx - 25, cy + 127, cx - 13, cy + 108, TFT_WHITE);
  epaper.fillTriangle(cx + 35, cy + 108, cx + 25, cy + 132, cx + 10, cy + 105, TFT_BLACK);
  epaper.fillTriangle(cx + 32, cy + 110, cx + 25, cy + 127, cx + 13, cy + 108, TFT_WHITE);

  // Happy upside-down eyes
  epaper.drawLine(cx - 22, cy + 78, cx - 14, cy + 72, TFT_BLACK);
  epaper.drawLine(cx - 14, cy + 72, cx - 6, cy + 78, TFT_BLACK);
  epaper.drawLine(cx + 6, cy + 78, cx + 14, cy + 72, TFT_BLACK);
  epaper.drawLine(cx + 14, cy + 72, cx + 22, cy + 78, TFT_BLACK);

  // Nose
  epaper.fillTriangle(cx - 3, cy + 88, cx + 3, cy + 88, cx, cy + 92, TFT_BLACK);

  // Smile
  epaper.drawLine(cx, cy + 92, cx - 8, cy + 97, TFT_BLACK);
  epaper.drawLine(cx, cy + 92, cx + 8, cy + 97, TFT_BLACK);

  // Paws in the air (all four sticking up)
  // Front left
  epaper.drawLine(cx - 45, cy - 20, cx - 70, cy - 80, TFT_BLACK);
  epaper.drawLine(cx - 44, cy - 20, cx - 69, cy - 80, TFT_BLACK);
  epaper.fillCircle(cx - 70, cy - 83, 12, TFT_BLACK);
  epaper.fillCircle(cx - 70, cy - 83, 7, TFT_WHITE);
  // Front right
  epaper.drawLine(cx + 45, cy - 20, cx + 70, cy - 80, TFT_BLACK);
  epaper.drawLine(cx + 44, cy - 20, cx + 69, cy - 80, TFT_BLACK);
  epaper.fillCircle(cx + 70, cy - 83, 12, TFT_BLACK);
  epaper.fillCircle(cx + 70, cy - 83, 7, TFT_WHITE);
  // Back left
  epaper.drawLine(cx - 30, cy + 40, cx - 55, cy - 20, TFT_BLACK);
  epaper.drawLine(cx - 29, cy + 40, cx - 54, cy - 20, TFT_BLACK);
  epaper.fillCircle(cx - 55, cy - 23, 10, TFT_BLACK);
  epaper.fillCircle(cx - 55, cy - 23, 6, TFT_WHITE);
  // Back right
  epaper.drawLine(cx + 30, cy + 40, cx + 55, cy - 20, TFT_BLACK);
  epaper.drawLine(cx + 29, cy + 40, cx + 54, cy - 20, TFT_BLACK);
  epaper.fillCircle(cx + 55, cy - 23, 10, TFT_BLACK);
  epaper.fillCircle(cx + 55, cy - 23, 6, TFT_WHITE);

  // Belly spot (round patch)
  epaper.drawCircle(cx, cy - 5, 20, TFT_BLACK);

  // Whiskers
  epaper.drawLine(cx - 15, cy + 90, cx - 50, cy + 82, TFT_BLACK);
  epaper.drawLine(cx - 15, cy + 93, cx - 50, cy + 93, TFT_BLACK);
  epaper.drawLine(cx + 15, cy + 90, cx + 50, cy + 82, TFT_BLACK);
  epaper.drawLine(cx + 15, cy + 93, cx + 50, cy + 93, TFT_BLACK);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Rub my belly!", cx, 420, 4);
}

// ---- Cat 22: Cool cat with sunglasses ----
void drawCat22()
{
  int cx = 600, cy = 200;

  // Body
  epaper.fillCircle(cx, cy + 60, 70, TFT_BLACK);
  epaper.fillCircle(cx, cy + 60, 64, TFT_WHITE);

  // Head
  epaper.fillCircle(cx, cy - 40, 55, TFT_BLACK);
  epaper.fillCircle(cx, cy - 40, 49, TFT_WHITE);

  // Ears
  epaper.fillTriangle(cx - 45, cy - 75, cx - 25, cy - 110, cx - 10, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx - 40, cy - 78, cx - 27, cy - 102, cx - 15, cy - 70, TFT_WHITE);
  epaper.fillTriangle(cx + 45, cy - 75, cx + 25, cy - 110, cx + 10, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx + 40, cy - 78, cx + 27, cy - 102, cx + 15, cy - 70, TFT_WHITE);

  // Sunglasses (solid black lenses)
  epaper.fillRect(cx - 38, cy - 55, 30, 18, TFT_BLACK);
  epaper.fillRect(cx + 8, cy - 55, 30, 18, TFT_BLACK);
  // Bridge
  epaper.drawLine(cx - 8, cy - 46, cx + 8, cy - 46, TFT_BLACK);
  epaper.drawLine(cx - 8, cy - 45, cx + 8, cy - 45, TFT_BLACK);
  // Arms of glasses
  epaper.drawLine(cx - 38, cy - 50, cx - 50, cy - 55, TFT_BLACK);
  epaper.drawLine(cx + 38, cy - 50, cx + 50, cy - 55, TFT_BLACK);
  // Shine on lenses
  epaper.drawLine(cx - 32, cy - 53, cx - 28, cy - 49, TFT_WHITE);
  epaper.drawLine(cx + 14, cy - 53, cx + 18, cy - 49, TFT_WHITE);

  // Nose
  epaper.fillTriangle(cx - 4, cy - 28, cx + 4, cy - 28, cx, cy - 23, TFT_BLACK);

  // Cool smirk
  epaper.drawLine(cx - 5, cy - 18, cx + 12, cy - 20, TFT_BLACK);
  epaper.drawLine(cx - 5, cy - 17, cx + 12, cy - 19, TFT_BLACK);

  // Whiskers
  epaper.drawLine(cx - 20, cy - 28, cx - 65, cy - 35, TFT_BLACK);
  epaper.drawLine(cx - 20, cy - 24, cx - 65, cy - 24, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 28, cx + 65, cy - 35, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 24, cx + 65, cy - 24, TFT_BLACK);

  // Front paws (crossed casually)
  epaper.drawLine(cx - 15, cy + 90, cx + 15, cy + 125, TFT_BLACK);
  epaper.drawLine(cx - 14, cy + 90, cx + 16, cy + 125, TFT_BLACK);
  epaper.fillCircle(cx + 18, cy + 128, 14, TFT_BLACK);
  epaper.fillCircle(cx + 18, cy + 128, 9, TFT_WHITE);
  epaper.drawLine(cx + 15, cy + 90, cx - 15, cy + 125, TFT_BLACK);
  epaper.drawLine(cx + 16, cy + 90, cx - 14, cy + 125, TFT_BLACK);
  epaper.fillCircle(cx - 18, cy + 128, 14, TFT_BLACK);
  epaper.fillCircle(cx - 18, cy + 128, 9, TFT_WHITE);

  // Tail
  for (int i = 0; i < 3; i++)
    epaper.drawCircle(cx + 85, cy + 75, 40 + i, TFT_BLACK);
  epaper.fillCircle(cx + 85, cy + 75, 38, TFT_WHITE);
  epaper.fillRect(cx - 5, cy + 35, 90, 70, TFT_WHITE);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Deal with it", cx, 420, 4);
}

// ---- Cat 23: Wizard cat (pointy hat) ----
void drawCat23()
{
  int cx = 600, cy = 220;

  // Body
  epaper.fillCircle(cx, cy + 50, 65, TFT_BLACK);
  epaper.fillCircle(cx, cy + 50, 59, TFT_WHITE);

  // Head
  epaper.fillCircle(cx, cy - 20, 48, TFT_BLACK);
  epaper.fillCircle(cx, cy - 20, 42, TFT_WHITE);

  // Wizard hat
  epaper.fillTriangle(cx - 45, cy - 52, cx, cy - 150, cx + 45, cy - 52, TFT_BLACK);
  epaper.fillTriangle(cx - 38, cy - 55, cx, cy - 140, cx + 38, cy - 55, TFT_WHITE);
  // Hat brim
  epaper.fillRect(cx - 55, cy - 58, 110, 10, TFT_BLACK);
  epaper.fillRect(cx - 52, cy - 55, 104, 4, TFT_WHITE);
  // Hat band
  epaper.fillRect(cx - 38, cy - 90, 76, 8, TFT_BLACK);
  // Star on hat
  // Simple star using triangles
  int sx = cx + 5, sy = cy - 110;
  epaper.fillTriangle(sx, sy - 8, sx - 6, sy + 4, sx + 6, sy + 4, TFT_WHITE);
  epaper.fillTriangle(sx, sy + 7, sx - 6, sy - 3, sx + 6, sy - 3, TFT_WHITE);

  // Ears (poking from under hat)
  epaper.fillTriangle(cx - 42, cy - 48, cx - 35, cy - 65, cx - 25, cy - 48, TFT_BLACK);
  epaper.fillTriangle(cx - 39, cy - 49, cx - 35, cy - 60, cx - 28, cy - 49, TFT_WHITE);
  epaper.fillTriangle(cx + 25, cy - 48, cx + 35, cy - 65, cx + 42, cy - 48, TFT_BLACK);
  epaper.fillTriangle(cx + 28, cy - 49, cx + 35, cy - 60, cx + 39, cy - 49, TFT_WHITE);

  // Mysterious eyes (glowing)
  epaper.fillCircle(cx - 18, cy - 25, 11, TFT_BLACK);
  epaper.fillCircle(cx + 18, cy - 25, 11, TFT_BLACK);
  epaper.fillCircle(cx - 18, cy - 25, 6, TFT_WHITE);
  epaper.fillCircle(cx + 18, cy - 25, 6, TFT_WHITE);
  epaper.fillCircle(cx - 18, cy - 25, 3, TFT_BLACK);
  epaper.fillCircle(cx + 18, cy - 25, 3, TFT_BLACK);

  // Nose
  epaper.fillTriangle(cx - 3, cy - 8, cx + 3, cy - 8, cx, cy - 3, TFT_BLACK);

  // Whiskers
  epaper.drawLine(cx - 18, cy - 5, cx - 55, cy - 12, TFT_BLACK);
  epaper.drawLine(cx - 18, cy - 2, cx - 55, cy - 2, TFT_BLACK);
  epaper.drawLine(cx + 18, cy - 5, cx + 55, cy - 12, TFT_BLACK);
  epaper.drawLine(cx + 18, cy - 2, cx + 55, cy - 2, TFT_BLACK);

  // Wand (held by paw)
  epaper.drawLine(cx + 55, cy + 80, cx + 100, cy - 30, TFT_BLACK);
  epaper.drawLine(cx + 56, cy + 80, cx + 101, cy - 30, TFT_BLACK);
  // Star at wand tip
  int wx = cx + 102, wy = cy - 35;
  epaper.fillCircle(wx, wy, 6, TFT_BLACK);
  epaper.fillCircle(wx, wy, 3, TFT_WHITE);
  // Sparkles
  epaper.drawLine(wx - 12, wy, wx + 12, wy, TFT_BLACK);
  epaper.drawLine(wx, wy - 12, wx, wy + 12, TFT_BLACK);
  epaper.drawLine(wx - 8, wy - 8, wx + 8, wy + 8, TFT_BLACK);
  epaper.drawLine(wx + 8, wy - 8, wx - 8, wy + 8, TFT_BLACK);

  // Paw holding wand
  epaper.fillCircle(cx + 55, cy + 83, 14, TFT_BLACK);
  epaper.fillCircle(cx + 55, cy + 83, 9, TFT_WHITE);

  // Other paw
  epaper.fillCircle(cx - 25, cy + 105, 16, TFT_BLACK);
  epaper.fillCircle(cx - 25, cy + 105, 11, TFT_WHITE);

  // Tail
  for (int i = 0; i < 3; i++)
    epaper.drawCircle(cx - 75, cy + 30, 35 + i, TFT_BLACK);
  epaper.fillCircle(cx - 75, cy + 30, 33, TFT_WHITE);
  epaper.fillRect(cx - 75, cy + 10, 80, 50, TFT_WHITE);
  epaper.fillRect(cx - 75, cy + 30, 30, 25, TFT_WHITE);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Meow-gic!", cx, 420, 4);
}
