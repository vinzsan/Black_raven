<?php

namespace App\Http\Controllers;

use App\Models\User;
use Illuminate\Support\Facades\Hash;
use Illuminate\Http\Request;

class AuthController extends Controller
{
    public function register(Request $request)
    {
        $request->validate([
            'username' => 'required|unique:users,username',
            'password' => 'required|min:3',
        ]);

        $password = Hash::make($request->password);

        User::create([
            'username' => $request->username,
            'password' => $password,
        ]);

        return response()->json([
            'message' => 'lu berhasil register coy'
        ]);
    }
}
