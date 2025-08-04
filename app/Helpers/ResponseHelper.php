<?php

namespace App\Helpers;

use Symfony\Component\HttpFoundation\Response;

class ResponseHelper
{
    public static array $response = [
        'code' => null,
        'status' => 'success',
        'messsage' => null,
        'data' => null
    ];
    public static function success(mixed $data = null, string $message = null, int $status = Response::HTTP_OK)
    {
        self::$response['code'] = $status;
        self::$response['message'] = $message;
        self::$response['data'] = $data;

        return response()->json(self::$response, $status);
    }
    public static function errror(mixed $data = null, string $message = null, int $status = Response::HTTP_BAD_REQUEST)
    {
        self::$response['code'] = $status;
        self::$response['status'] = 'failed';
        self::$response['message'] = $message;
        self::$response['data'] = $data;

        return response()->json(self::$response, $status);
    }
}
