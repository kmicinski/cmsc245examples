; I took most of this from Matt Might's:
; http://matt.might.net/articles/lexers-in-racket/
#lang racket
(require parser-tools/lex)
(require (prefix-in : parser-tools/lex-sre))

;(struct char (c) #:)

(define lex
 (lexer
    ; skip spaces:
    [#\space     (lex input-port)]
    ; skip newline:
    [#\newline   (lex input-port)]

    [#\+         'plus]
    [#\-         'minus]
    [#\*         'times]
    [#\/         'div]

    [(:: (:? #\-) (:+ (char-range #\0 #\9))) (string->number lexeme)]
    ; an actual character:
    [any-char    (string-ref lexeme 0)]))

(define ab-test-in (open-input-string "1 + 2 * 3 + 4 * 1 + 3")); , aabbaa
      
(define (next-tok)
  (lex ab-test-in))

(define curtok (next-tok))

(define (accept c)
  (if (not (equal? curtok c))
      (raise 'unexpected-token)
      (begin
        (printf "Accepting ~a\n" c)
        (set! curtok (next-tok)))))

;; Example 1

(define (parse-A)
  (match curtok
    [#\a
     (begin
       (accept #\a)
       (parse-A)
       (accept #\a))]
    [#\b (parse-B)]))

(define (parse-B)
  (begin
    (accept #\b)
    (accept #\b)))

;; Example 2
;1 + 2 + 3 + 4
(define (parse-num)
  (match curtok
    (number? (begin (let ([c curtok]) (accept curtok) c)))))

(define (parse-Plus)
  (begin
    (parse-num)
    (parse-MorePlus)))

(define (parse-MorePlus)
  (match curtok
    ['plus
     (begin
       (accept 'plus)
       (parse-num)
       (parse-MorePlus))]
    ['eof (void)]))

;; Example 3
;; "1 + 2 * 3 + 4 * 1 + 3"

; Add -> Term MoreTerms
(define (parse-Add)
  (begin
    ; ^ Term MoreTerms
    (parse-Term)
    ; Term ^ MoreTerms
    (parse-MoreTerms)
    ; Term MoreTerms ^
    ))

; MoreTerms -> + Term MoreTerms | epsilon
(define (parse-MoreTerms)
  (match curtok
    ; FOLLOW(MoreTerms) includes 'eof, and MoreTerms is NULLABLE
    ['eof (void)]
    ; ^ + Term
    ['plus
     (begin
       (accept 'plus)
       ; + ^ Term MoreTerms
       (parse-Term)
       ; + Term ^ MoreTerms
       (parse-MoreTerms)
       ; + Term MoreTerms ^
       )]))

; Term -> num MoreNums
(define (parse-Term)
  (begin
    (parse-num)
    ; num ^ MoreNums
    (parse-MoreNums)
    ; num MoreNums ^
    ))

; MoreNums -> * num MoreNums | epsilon
(define (parse-MoreNums)
  (match curtok
    ['times
     (begin
       ; ^ * num MoreNums
       (accept 'times)
       ; * ^ num MoreNums
       (parse-num)
       ; * num ^ MoreNums
       (parse-MoreNums)
       ; * num MoreNums ^
       )]
    ; Either of these are in FOLLOW(MoreNums)
    ['plus (void)]
    ['eof (void)]))

; Grammar for minus
; <Minus> ::= number ( + number ) *

; Example 4: 
(struct add (left right) #:transparent)
(struct times (left right) #:transparent)

(define (parse-Add-t)
    (let ([left (parse-Term-t)]
          [right (parse-MoreTerms-t)])
      (if (void? right)
          left
          (add left right))))

(define (parse-MoreTerms-t)
  (match curtok
    ['eof (void)]
    ['plus
     (begin
       (accept 'plus)
       (let ([left (parse-Term-t)]
             [right (parse-MoreTerms-t)])
         (if (void? right)
             left
             (add left right))))]))

(define (parse-Term-t)
  (let ([left (parse-num)]
        [right (parse-MoreNums-t)])
    (if (void? right)
        left
        (times left right))))

(define (parse-MoreNums-t)
  (match curtok
    ['times
     (begin
       (accept 'times)
       (let ([left (parse-num)]
             [right (parse-MoreNums-t)])
         (if (void? right)
             left
             (times left right))))]
    ['plus (void)]
    ['eof (void)]))



