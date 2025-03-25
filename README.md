# Shader Based Space Simulation (Practice Project)

🚀 **Açıklama:**
Bu proje, shader tabanlı OpenGL 3.2+ kullanılarak yapılmış basit bir uzay simülasyonu denemesidir.  
Freelance bir iş kapsamında yapılmaya başlanmış, ancak belirli nedenlerle tamamlanamamıştır.  
Yine de öğrenim sürecinin bir parçası olarak burada arşivlenmiştir.

---

## 💡 Teknolojiler

- C++  
- OpenGL 3.2+  
- GLSL Shader  
- GLUT & GLEW  
- Visual Studio 2019/2022

---

## 🎮 Kontroller

| Tuş | Açıklama |
|-----|----------|
| `a/d` | Uzay gemisini döndür |
| `j/k` | Uzay istasyonunun dönüş hızını ayarla |
| `w/s` | Gemiyi ileri/geri kaydır |
| `p` | Pause / Devam |
| `o` | Tek adım ilerletme |
| `c` | Renk değiştir + mod geçiş |
| `ESC` | Çıkış |

---

## ⚙️ Derleme ve Çalıştırma

**Gereksinimler:**

- Visual Studio (Windows)
- GLEW & GLUT kütüphaneleri
- Shader dosyaları `shaders/` klasöründe olmalı

**Derlemek için:**
```bash
g++ src/main.cpp src/initshader.cpp -o ShaderSim.exe -lglew32 -lfreeglut -lopengl32
