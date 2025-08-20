<?php

namespace App\Http\Services;

use App\Helpers\ResponseHelper;
use App\Http\Requests\LoginRequest;
use App\Http\Requests\RegisterRequest;
use Hash;
use App\Models\User;
use Symfony\Component\HttpFoundation\Response;
use Auth;

class AuthService
{
    public function handleRegister(RegisterRequest $request)
    {
        $validated = $request->validated();

        $user = User::create($validated);

        return (object) [
            'user' => $user,
            'token' => $user->createToken('auth-token')->plainTextToken,
        ];
    }

    public function handleLogin(LoginRequest $request)
    {
        $validated = $request->validated();

        if (!Auth::attempt($validated)) return ResponseHelper::errror(message: 'gagal login', status: Response::HTTP_UNAUTHORIZED);

        $user = User::where('username', $validated['username']);

        return (object) [
            'user' => $user,
            'token' => $user->createToken('auth-token')->plainTextToken,
        ];
    }
}
