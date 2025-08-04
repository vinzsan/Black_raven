<?php

namespace App\Http\Controllers;

use App\Helpers\ResponseHelper;
use App\Http\Requests\LoginRequest;
use App\Http\Requests\RegisterRequest;
use App\Models\User;
use Illuminate\Support\Facades\Hash;
use Illuminate\Http\Request;
use App\Http\Services\AuthService;
use Symfony\Component\HttpKernel\Event\ResponseEvent;

class AuthController extends Controller
{
    private AuthService $authService;

    public function __construct(AuthService $authService)
    {
        $this->authService = $authService;
    }

    public function register(RegisterRequest $request)
    {
        try {
            return ResponseHelper::success($this->authService->handleRegister($request), 'berhasil register');
        } catch (\Throwable $thrw) {
            return ResponseHelper::errror(message: 'gagal register');
        }
    }

    public function login(LoginRequest $request)
    {
        try {
            return ResponseHelper::success($this->authService->handleLogin($request), 'berhasil login');
        } catch (\Throwable $thrw) {
            return ResponseHelper::errror(message: 'gagal login');
        }
    }
}
