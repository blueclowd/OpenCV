# An improved Halftone Visual Secret Sharing Scheme for gray-level images based on error diffusion in forward and backward direction

#### Author
- Aman Kamboj
- D.K.Gupta

#### Visual Secret Sharing
  - An Information hiding scheme since 1995.
  - Use image to protect the secret.
  - One can think of it as the inverse of watermark since watermark use a secret to protect the image.
  - Reveal the secret by HVS (Human Visual System) without computation.

#### Proposed Scheme
![Input][input]
![Secret][secret]

[input]: https://raw.githubusercontent.com/blueclowd/OpenCV/master/An%20improved%20Halftone%20Visual%20Secret%20Sharing%20Scheme%20for%20gray-level%20images%20based%20on%20error%20diffusion%20in%20forward%20and%20backward%20direction/image/LennaGray.png "Input image"
[secret]: https://raw.githubusercontent.com/blueclowd/OpenCV/master/An%20improved%20Halftone%20Visual%20Secret%20Sharing%20Scheme%20for%20gray-level%20images%20based%20on%20error%20diffusion%20in%20forward%20and%20backward%20direction/image/cameraman.jpg "Secret image"

##### Phase 1: Halftoning process

![HalfTone][halfTone]
![invHalfTone][invHalfTone]

[halfTone]: https://raw.githubusercontent.com/blueclowd/OpenCV/master/An%20improved%20Halftone%20Visual%20Secret%20Sharing%20Scheme%20for%20gray-level%20images%20based%20on%20error%20diffusion%20in%20forward%20and%20backward%20direction/image/halfTone.png "HalfTone image"
[invHalfTone]: https://raw.githubusercontent.com/blueclowd/OpenCV/master/An%20improved%20Halftone%20Visual%20Secret%20Sharing%20Scheme%20for%20gray-level%20images%20based%20on%20error%20diffusion%20in%20forward%20and%20backward%20direction/image/inv_halfTone.png "Inverse of halfTone"

##### Phase 2: Encryption Process
![Share1][share1]
![Share2][share2]

[share1]: https://raw.githubusercontent.com/blueclowd/OpenCV/master/An%20improved%20Halftone%20Visual%20Secret%20Sharing%20Scheme%20for%20gray-level%20images%20based%20on%20error%20diffusion%20in%20forward%20and%20backward%20direction/image/Share1.png "Share1"
[share2]: https://raw.githubusercontent.com/blueclowd/OpenCV/master/An%20improved%20Halftone%20Visual%20Secret%20Sharing%20Scheme%20for%20gray-level%20images%20based%20on%20error%20diffusion%20in%20forward%20and%20backward%20direction/image/Share2.png "Share2"

##### Phase 3: Decryption Process

![Reconstrutcted][reconstructed]

[reconstructed]: https://raw.githubusercontent.com/blueclowd/OpenCV/master/An%20improved%20Halftone%20Visual%20Secret%20Sharing%20Scheme%20for%20gray-level%20images%20based%20on%20error%20diffusion%20in%20forward%20and%20backward%20direction/image/Superimposed.png "reconstructed"

#### Note

> It is implemented using OpenCV 3.1.0 on Ubuntu 14.04


