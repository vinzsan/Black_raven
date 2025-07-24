## Made with

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![PHP](https://img.shields.io/badge/php-%23777BB4.svg?style=for-the-badge&logo=php&logoColor=white)

p align="center"><a href="https://laravel.com" target="_blank"><img src="https://raw.githubusercontent.com/laravel/art/master/logo-lockup/5%20SVG/2%20CMYK/1%20Full%20Color/laravel-logolockup-cmyk-red.svg" width="400" alt="Laravel Logo"></a></p>

<p align="center">
<a href="https://github.com/laravel/framework/actions"><img src="https://github.com/laravel/framework/workflows/tests/badge.svg" alt="Build Status"></a>
<a href="https://packagist.org/packages/laravel/framework"><img src="https://img.shields.io/packagist/dt/laravel/framework" alt="Total Downloads"></a>
<a href="https://packagist.org/packages/laravel/framework"><img src="https://img.shields.io/packagist/v/laravel/framework" alt="Latest Stable Version"></a>
<a href="https://packagist.org/packages/laravel/framework"><img src="https://img.shields.io/packagist/l/laravel/framework" alt="License"></a>
</p>

# 🛠️ PixelCraft — Game Sederhana Terinspirasi dari Terraria

PixelCraft adalah game 2D pixel sandbox sederhana yang terinspirasi dari *Terraria*, dibangun menggunakan **SDL2** untuk frontend gamenya dan **Laravel PHP** sebagai backend API. Game ini mendukung fitur seperti:

- Gerakan karakter 2D, lompat, dan mining
- World dengan sistem blok sederhana (dapat disimpan)
- Login dan penyimpanan data pemain (via Laravel API)
- Leaderboard dan sistem online sederhana

---

## 🎮 Fitur Game (SDL2 + C)
- Grafis 2D dengan tile-based map
- Karakter bergerak dan animasi frame sprite
- Sistem blok: tempatkan & hancurkan
- UI dasar: health bar, hotbar
- Sistem save/load world dari file atau API

---

## 🌐 Backend (Laravel API)
Backend Laravel menangani:
- **Registrasi & Login pengguna**
- **Penyimpanan world per user**
- **Leaderboard skor global**
- **Penyimpanan progress dan statistik player**

---

## 🧩 Struktur Proyek
