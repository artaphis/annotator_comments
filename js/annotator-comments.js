(function ($) {

  Drupal.behaviors.annotatorComments = {
    attach: function (context, settings) {

      Annotator.Plugin.AnnotatorComments = function (element) {
        var annotatorComments = {};

        annotatorComments.reloadPage = function () {
          setTimeout(function () {
            location.reload(true);
          }, 2000);
        };

        annotatorComments.pluginInit = function () {
          var annotator = this.annotator;
          var annotations = annotator.dumpAnnotations();

          annotator
            .subscribe('annotationsLoaded',function (annotations) {
              for (var i = 0; i < annotations.length; i++) {
                $('#comment-' + annotations[i].id + ' + .comment').addClass('annotated').data('annotation', annotations[i]);
              }

              $.each($('.comment.annotated'), function () {
                var comment = $(this);

                comment.mouseenter(function () {
                  var annotation = comment.data('annotation');
                  if (annotation) {
                    $(annotation.highlights).addClass('annotator-hl-linked');
                  }
                });

                comment.mouseleave(function () {
                  var annotation = comment.data('annotation');
                  if (annotation) {
                    $(annotation.highlights).removeClass('annotator-hl-linked');
                  }
                });

              });
            }).subscribe('annotationCreated',function (annotation) {
              annotatorComments.reloadPage();
            }).subscribe('annotationUpdated',function (annotation) {
              annotatorComments.reloadPage();
            }).subscribe('annotationDeleted', function (annotation) {
              annotatorComments.reloadPage();
            });
        };

        return annotatorComments;
      };

      var nid = Drupal.settings.annotatorComments.nid;
      var content = $('.node .content').annotator();

      content.annotator('addPlugin', 'Store', {
        prefix: Drupal.settings.basePath + 'ajax/annotator-comments/' + nid,
        annotationData: {
          nid: nid
        }
      }).annotator('addPlugin', 'AnnotatorComments');

    }
  };

})(jQuery);
