#include <SPI.h>
#include <TFT_eSPI.h>

#ifdef EPAPER_ENABLE

EPaper epaper = EPaper();

int currentCat = 0;
uint32_t targetTime = 0;

// Forward declarations
void drawCat0();
void drawCat1();
void drawCat2();
void drawCat3();
void drawCat4();

void drawCurrentCat()
{
  epaper.fillScreen(TFT_WHITE);

  switch (currentCat)
  {
  case 0:
    drawCat0();
    break;
  case 1:
    drawCat1();
    break;
  case 2:
    drawCat2();
    break;
  case 3:
    drawCat3();
    break;
  case 4:
    drawCat4();
    break;
  }

  epaper.update();
}

// --- Cat 0: Sitting cat (front-facing, tail curled) ---
void drawCat0()
{
  int cx = 400, cy = 200;

  // Body (oval-ish using overlapping circles)
  epaper.fillCircle(cx, cy + 60, 70, TFT_BLACK);
  epaper.fillCircle(cx, cy + 60, 64, TFT_WHITE);

  // Head
  epaper.fillCircle(cx, cy - 40, 55, TFT_BLACK);
  epaper.fillCircle(cx, cy - 40, 49, TFT_WHITE);

  // Ears (triangles)
  epaper.fillTriangle(cx - 45, cy - 75, cx - 25, cy - 110, cx - 10, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx - 40, cy - 78, cx - 27, cy - 102, cx - 15, cy - 70, TFT_WHITE);
  epaper.fillTriangle(cx + 45, cy - 75, cx + 25, cy - 110, cx + 10, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx + 40, cy - 78, cx + 27, cy - 102, cx + 15, cy - 70, TFT_WHITE);

  // Eyes
  epaper.fillCircle(cx - 20, cy - 45, 10, TFT_BLACK);
  epaper.fillCircle(cx + 20, cy - 45, 10, TFT_BLACK);
  epaper.fillCircle(cx - 18, cy - 47, 4, TFT_WHITE); // highlights
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
  // Erase inside of tail arc to make it look like a curve
  epaper.fillCircle(cx + 80, cy + 80, 37, TFT_WHITE);
  // Erase left half to show only the curl
  epaper.fillRect(cx - 10, cy + 40, 90, 85, TFT_WHITE);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Hello, I'm sitting here!", cx, 420, 4);
}

// --- Cat 1: Sleeping cat (curled up, zzz) ---
void drawCat1()
{
  int cx = 400, cy = 220;

  // Curled body (big circle)
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

  // Closed eyes (horizontal lines)
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
  // Erase to show only tip of tail
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

// --- Cat 2: Playful cat (paw raised, wide eyes) ---
void drawCat2()
{
  int cx = 400, cy = 200;

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

  // Big wide eyes (larger than normal)
  epaper.fillCircle(cx - 22, cy - 48, 14, TFT_BLACK);
  epaper.fillCircle(cx + 22, cy - 48, 14, TFT_BLACK);
  epaper.fillCircle(cx - 18, cy - 52, 6, TFT_WHITE);
  epaper.fillCircle(cx + 26, cy - 52, 6, TFT_WHITE);
  epaper.fillCircle(cx - 24, cy - 44, 3, TFT_WHITE);
  epaper.fillCircle(cx + 20, cy - 44, 3, TFT_WHITE);

  // Nose
  epaper.fillTriangle(cx - 4, cy - 28, cx + 4, cy - 28, cx, cy - 23, TFT_BLACK);

  // Open mouth (excited)
  epaper.drawLine(cx, cy - 23, cx - 10, cy - 15, TFT_BLACK);
  epaper.drawLine(cx, cy - 23, cx + 10, cy - 15, TFT_BLACK);
  epaper.drawLine(cx - 10, cy - 15, cx + 10, cy - 15, TFT_BLACK);

  // Whiskers
  epaper.drawLine(cx - 20, cy - 30, cx - 65, cy - 40, TFT_BLACK);
  epaper.drawLine(cx - 20, cy - 25, cx - 65, cy - 25, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 30, cx + 65, cy - 40, TFT_BLACK);
  epaper.drawLine(cx + 20, cy - 25, cx + 65, cy - 25, TFT_BLACK);

  // Right paw raised up
  epaper.drawLine(cx + 50, cy + 30, cx + 90, cy - 20, TFT_BLACK);
  epaper.drawLine(cx + 52, cy + 30, cx + 92, cy - 20, TFT_BLACK);
  // Paw at end of raised arm
  epaper.fillCircle(cx + 91, cy - 25, 15, TFT_BLACK);
  epaper.fillCircle(cx + 91, cy - 25, 10, TFT_WHITE);
  // Toe beans
  epaper.fillCircle(cx + 85, cy - 35, 4, TFT_BLACK);
  epaper.fillCircle(cx + 95, cy - 35, 4, TFT_BLACK);
  epaper.fillCircle(cx + 100, cy - 26, 4, TFT_BLACK);

  // Left paw (on ground)
  epaper.fillCircle(cx - 25, cy + 120, 18, TFT_BLACK);
  epaper.fillCircle(cx - 25, cy + 120, 13, TFT_WHITE);

  // Tail (upright, excited)
  epaper.drawLine(cx + 60, cy + 100, cx + 85, cy - 10, TFT_BLACK);
  epaper.drawLine(cx + 61, cy + 100, cx + 86, cy - 10, TFT_BLACK);
  epaper.drawLine(cx + 62, cy + 100, cx + 87, cy - 10, TFT_BLACK);
  // Tail tip curl
  epaper.drawLine(cx + 86, cy - 10, cx + 75, cy - 25, TFT_BLACK);
  epaper.drawLine(cx + 87, cy - 10, cx + 76, cy - 25, TFT_BLACK);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Play with me!", cx, 420, 4);
}

// --- Cat 3: Grumpy cat (furrowed brows, frown) ---
void drawCat3()
{
  int cx = 400, cy = 200;

  // Body
  epaper.fillCircle(cx, cy + 60, 70, TFT_BLACK);
  epaper.fillCircle(cx, cy + 60, 64, TFT_WHITE);

  // Head
  epaper.fillCircle(cx, cy - 40, 55, TFT_BLACK);
  epaper.fillCircle(cx, cy - 40, 49, TFT_WHITE);

  // Ears (slightly flattened — wider)
  epaper.fillTriangle(cx - 50, cy - 70, cx - 30, cy - 108, cx - 8, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx - 45, cy - 73, cx - 30, cy - 100, cx - 13, cy - 70, TFT_WHITE);
  epaper.fillTriangle(cx + 50, cy - 70, cx + 30, cy - 108, cx + 8, cy - 65, TFT_BLACK);
  epaper.fillTriangle(cx + 45, cy - 73, cx + 30, cy - 100, cx + 13, cy - 70, TFT_WHITE);

  // Angry eyes (half-closed)
  epaper.fillCircle(cx - 20, cy - 45, 10, TFT_BLACK);
  epaper.fillCircle(cx + 20, cy - 45, 10, TFT_BLACK);
  epaper.fillCircle(cx - 18, cy - 47, 4, TFT_WHITE);
  epaper.fillCircle(cx + 22, cy - 47, 4, TFT_WHITE);

  // Furrowed brows (angry V shapes)
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

// --- Cat 4: Cat with fish (happy cat, fish beside) ---
void drawCat4()
{
  int cx = 350, cy = 200; // Shifted left to make room for fish

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

  // Happy eyes (closed, upward arcs shown as ^ shapes)
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
  int fx = 550, fy = 160;

  // Fish body (ellipse approximation with overlapping circles)
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
  // Simple heart: two small circles + triangle
  int hx = 470, hy = 120;
  epaper.fillCircle(hx - 6, hy - 4, 6, TFT_BLACK);
  epaper.fillCircle(hx + 6, hy - 4, 6, TFT_BLACK);
  epaper.fillTriangle(hx - 12, hy - 2, hx + 12, hy - 2, hx, hy + 14, TFT_BLACK);

  // Smaller heart
  int hx2 = 490, hy2 = 100;
  epaper.fillCircle(hx2 - 4, hy2 - 3, 4, TFT_BLACK);
  epaper.fillCircle(hx2 + 4, hy2 - 3, 4, TFT_BLACK);
  epaper.fillTriangle(hx2 - 8, hy2 - 1, hx2 + 8, hy2 - 1, hx2, hy2 + 10, TFT_BLACK);

  // Caption
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);
  epaper.drawCentreString("Fish is life <3", 400, 420, 4);
}

#endif

void setup()
{
#ifdef EPAPER_ENABLE
  epaper.begin();
  epaper.setRotation(0);
  epaper.setTextColor(TFT_BLACK, TFT_WHITE);

  drawCurrentCat();
  targetTime = millis() + 60000;
#endif
}

void loop()
{
#ifdef EPAPER_ENABLE
  if (millis() > targetTime)
  {
    currentCat = (currentCat + 1) % 5;
    drawCurrentCat();
    targetTime = millis() + 60000;
  }
#endif
}
