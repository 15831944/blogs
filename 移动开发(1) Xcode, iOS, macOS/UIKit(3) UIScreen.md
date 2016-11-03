# iPhone 的尺寸

| model        | size | resolution | times | size        |
| ------------ | ---- | ---------- | ----- | ----------- |
| 3GS          | 3.5  | 320 * 480  | @1x   | 320 * 480   |
| 4/4s         | 3.5  | 320 * 480  | @2x   | 640 * 960   |
| 5/5s/5c      | 4.0  | 320 * 568  | @2x   | 640 * 1136  |
| 6/6s         | 4.7  | 375 * 667  | @2x   | 750 * 1334  |
| 6plus/6splus | 5.5  | 414 * 736  | @3x   | 1242 * 2208 |

# UIScreen

获取屏幕大小

`float width = [[UIScreen mainScreen] bounds].size.width;`

`float height = [[UIScreen mainScreen] bounds].size.height;`
