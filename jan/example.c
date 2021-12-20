#define UNICODE
#include <windows.h>
#define CANVAS_IMPLEMENTATION
#define CANVAS_ENABLE_TEXT
#include "canvas.h"
#include "jan/jan.h"

int width;
int height;
Canvas *canvas;
JanContext *context;
JanBox *root;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_CREATE) {
        canvas = Canvas_New(hwnd, CANVAS_RENDERER_DEFAULT);

        context = JanContext_New(canvas);
        JanContext_SetDebug(context, true);

        root = JanBox_New(context, JAN_ORIENTATION_VERTICAL);
        JanBox_SetWidth(root, JAN_UNIT(100, JAN_UNIT_TYPE_PERCENT));
        JanBox_SetHeight(root, JAN_UNIT_WRAP);
        JanBox_SetPaddingLeft(root, JAN_UNIT(10, JAN_UNIT_TYPE_VW));
        JanBox_SetPaddingRight(root, JAN_UNIT(10, JAN_UNIT_TYPE_VW));
        JanBox_SetBackgroundColor(root, JAN_COLOR_RGB(0, 128, 128));

        for (int32_t y = 0; y < 5; y++) {
            JanBox *row = JanBox_New(context, JAN_ORIENTATION_HORIZONTAL);
            JanBox_SetHeight(row, JAN_UNIT(32, JAN_UNIT_TYPE_DP));
            JanBox_ChildrenAdd(root, OBJECT(row));

            for (int32_t x = 0; x < 10; x++) {
                wchar_t buffer[200];
                wsprintf(buffer, L"Line %dx%d", x + 1, y + 1);
                JanLabel *label = JanLabel_New(context, buffer);
                JanLabel_SetSingleLine(label, true);
                JanBin_SetPaddingTop(label, JAN_UNIT(16, JAN_UNIT_TYPE_DP));
                JanBin_SetPaddingLeft(label, JAN_UNIT(16, JAN_UNIT_TYPE_DP));
                JanBin_SetPaddingRight(label, JAN_UNIT(16, JAN_UNIT_TYPE_DP));
                JanBin_SetPaddingBottom(label, JAN_UNIT(16, JAN_UNIT_TYPE_DP));
                JanBox_ChildrenAdd(row, OBJECT(label));
            }
        }

        JanBox_ChildrenAdd(root, OBJECT(JanLabel_New(context, L"Lorem ipsum dolor sit amet consectetur adipisicing elit. Ea accusamus quod, doloribus nihil autem consectetur quasi? Aspernatur cumque incidunt quod dicta voluptates nobis, sed cum dolore aperiam et ex minus ad vel eos quam reiciendis placeat corrupti reprehenderit consectetur consequuntur, in sequi. Perspiciatis dolorem, eveniet, fuga autem, officia explicabo quas earum iure aliquid id perferendis? Eum laborum ex repellendus hic reiciendis, cumque alias inventore modi aut est iure, aliquam ipsum quas! Officia dolore totam ipsa adipisci iste autem numquam necessitatibus nam ratione aspernatur aliquam ducimus mollitia non et, laudantium, expedita explicabo? Voluptate amet fugit modi nemo dolore adipisci dolorum, exercitationem rem, dignissimos blanditiis ex aut asperiores neque cum ratione quibusdam sit harum assumenda quasi tempora totam nobis sapiente? Omnis eligendi rem commodi nam, porro itaque soluta enim. Tempora necessitatibus distinctio accusamus similique aliquid soluta quibusdam, iste nostrum voluptatibus inventore veritatis commodi omnis ducimus, ipsa explicabo maiores. Repudiandae aperiam nesciunt facere quae numquam doloremque incidunt iste libero dolorum vitae, quis optio odit suscipit culpa aliquam in sequi deserunt voluptates facilis cupiditate nisi et sapiente. Veniam ducimus impedit consectetur doloribus nulla! Illo voluptatem ducimus expedita reiciendis rem blanditiis suscipit quam esse quia ab reprehenderit, aut facere rerum magnam itaque autem libero eius.")));

        JanBox *buttons = JanBox_New(context, JAN_ORIENTATION_HORIZONTAL);
        JanBox_ChildrenAdd(root, OBJECT(buttons));
        JanBox_ChildrenAdd(buttons, OBJECT(JanButton_New(context, L"Play")));
        JanBox_ChildrenAdd(buttons, OBJECT(JanButton_New(context, L"Settings")));
        JanBox_ChildrenAdd(buttons, OBJECT(JanButton_New(context, L"Exit")));

        return 0;
    }

    if (msg == WM_SIZE) {
        JanContext_Resize(context, LOWORD(lParam), HIWORD(lParam), 96);
        Canvas_Resize(canvas, LOWORD(lParam), HIWORD(lParam), 96);

        JanWidget_Measure(root, context->width, context->height);
        JanWidget_Place(root, 0, 0);
        return 0;
    }

    if (msg == WM_PAINT) {
        Canvas_BeginDraw(canvas);

        Canvas_FillRect(canvas, &(CanvasRect){ 0, 0, canvas->width, canvas->height }, CANVAS_RGB(0, 0, 0));

        JanWidget_Draw(root);

        Canvas_EndDraw(canvas);
        return 0;
    }

    if (msg == WM_DESTROY) {
        JanBox_Free(root);
        JanContext_Free(context);
        Canvas_Free(canvas);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"jan-example";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&wc);

    HWND hwnd = CreateWindowEx(0, wc.lpszClassName, L"Jan GUI Example", WS_OVERLAPPEDWINDOW,
        100, 100, 1024, 768, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG message;
    while (GetMessage(&message, NULL, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    return message.wParam;
}
